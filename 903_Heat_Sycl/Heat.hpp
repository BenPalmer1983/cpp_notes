#ifndef HEAT_HPP
#define HEAT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <omp.h>
#include <sycl/sycl.hpp>
#include "json.hpp"
#include "Grid.hpp"
#include "Source.hpp"
#include "Writer.hpp"
#include "SyclEngine.hpp"




SYCL_EXTERNAL inline double source_value_at_device(
    const Source& s,
    double t, double x, double y,
    double dt, double dx, double dy)
{
    // Temporal gating
    bool active = false;
    switch (s.temporal_kind) 
    {
        case Source::TemporalKind::Constant:
        case Source::TemporalKind::Rate:
        {
            active = (t >= s.t0) && (t < s.t0 + s.duration);
            break;
        }
        case Source::TemporalKind::Impulse:
        {
            // discrete impulse in the step that contains t0
            active = (t >= s.t0) && (t < s.t0 + dt);
            break;
        }
    }
    if (!active) return 0.0;

    // Spatial profile
    double spatial = 0.0;
    switch (s.spatial_kind) {
        case Source::SpatialKind::Gaussian: 
        {
            const double dx0 = x - s.x0;
            const double dy0 = y - s.y0;
            const double two_sigma2 = 2.0 * s.sigma * s.sigma + 1e-300;
            spatial = sycl::exp(-(dx0*dx0 + dy0*dy0) / two_sigma2);
            break;
        }
        case Source::SpatialKind::Block:
        {
            spatial = (x >= s.x_min && x <= s.x_max &&
                       y >= s.y_min && y <= s.y_max) ? 1.0 : 0.0;
            break;
        }
        case Source::SpatialKind::Point: {
            // Act only on the cell that contains (x0, y0)
            const double hx = 0.5 * dx;
            const double hy = 0.5 * dy;
            spatial = (sycl::fabs(x - s.x0) <= hx && sycl::fabs(y - s.y0) <= hy) ? 1.0 : 0.0;
            break;
        }
    }
    return s.amplitude * spatial;
}




class Heat
{

public:

    static void run(std::string& input_file)
    {

        auto start = std::chrono::high_resolution_clock::now();

        std::string device {};
        Grid model_grid {};
        std::vector<Source> sources {};
        double dt {};
        double t_final {};
        int snapshot_every {};
        std::filesystem::path outdir {};
        std::filesystem::path prefix {};
        bool queue_output {};

        // Read input
        Heat::read_input(input_file, device, model_grid, sources, dt, t_final, snapshot_every, outdir, prefix, queue_output);

        // Make output dir
        try 
        {
            std::filesystem::create_directory(outdir);
        } 
        catch (const std::filesystem::filesystem_error& e) 
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Set up sycl engine (will store grid and sources on device)
        SyclEngine sycl_engine {device, model_grid.nx, model_grid.ny, sources.size()};

        // Heat grid
        Heat::heat_grid_sycl(sycl_engine, model_grid, sources, dt, t_final, snapshot_every, outdir, prefix, queue_output);

        // Record end time
        auto end = std::chrono::high_resolution_clock::now();

        // Compute duration in milliseconds
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Execution time: " << duration.count() << " ms\n";
    }


private:    

    // Calculate root squared sum
    static double rss(const std::vector<double>& a) 
    {
        double sum {};
        for (double v : a)
        {
            sum += (v * v) / a.size();
        }
        return std::sqrt(sum);
    }



    static void read_input( std::string& input_file, 
                            std::string& device,
                            Grid& model_grid, 
                            std::vector<Source>& sources , 
                            double& dt, 
                            double& t_final,
                            int& snapshot_every,
                            std::filesystem::path& outdir,
                            std::filesystem::path& prefix,
                            bool& queue_output
                        )
    {

        // Try reading config file
        std::ifstream in(input_file);
        if (!in) 
        {
            throw std::runtime_error(std::string("Cannot open config file: ") + input_file);
        }

        // Read in
        nlohmann::json config_file;
        in >> config_file;

        // Read selected device
        device = config_file.at("device").get<std::string>();
        
        // Set up the 2D model grid and load alpha/thermal diffusivity regions
        model_grid = Grid::Load_settings(config_file);
        set_alpha_regions(model_grid, config_file.at("alpha"));

        dt = config_file.value("dt", 0.0);
        t_final = config_file.at("t_final").get<double>();
        if (t_final <= 0.0) throw std::runtime_error("t_final must be > 0");

        snapshot_every = std::max(1, config_file.value("snapshot_every", 100));
        outdir = config_file.value("output_dir", std::filesystem::path("out"));
        prefix = config_file.value("output_prefix", std::filesystem::path("heat"));
        queue_output = config_file.value("queue_output", true);

        // Zero out the boundaries of the grid
        Grid::dirichlet_boundaries(model_grid);

        // Parse sources (optional)
        sources = parse_sources(config_file, model_grid);

        double alpha_max = *std::max_element(model_grid.alpha.begin(), model_grid.alpha.end());
        if (alpha_max <= 0) throw std::runtime_error("alpha must be > 0");

        double dt_max = 1.0 / (2.0 * alpha_max * (model_grid.invdx2 + model_grid.invdy2));
        if (dt <= 0.0 || dt > dt_max) 
        {
            double chosen = 0.9 * dt_max;
            if (dt > 0.0 && dt > dt_max) 
            {
                std::cerr << "Warning: provided dt=" << dt
                          << " is unstable; using 0.9*dt_max=" << chosen << "\n";
            }
            dt = chosen;
        }
    }


    static void heat_grid_sycl(  
        SyclEngine& sycl_engine,
        Grid& model_grid, 
        const std::vector<Source>& sources, 
        const double& dt, 
        const double& t_final,
        const int& snapshot_every,
        const std::filesystem::path& outdir,
        const std::filesystem::path& prefix,
        const bool queue_output
    )
    {

        // Start a snapshot writer
        Writer writer;

        // Meta model_grid for snapshot writer
        Grid meta = model_grid;
        meta.u.clear();


        double t = 0.0;
        long long step = 0;

        // Save grid to file (at t=0)   
        if(queue_output)
        {      
            writer.enqueue(prefix, outdir, t, step, model_grid);
        }
        else
        {
            writer.grid_to_csv(prefix, outdir, t, step, model_grid);
        }

        // Upload grid + sources (scalars & arrays)
        sycl_engine.upload_grid(model_grid, sources);
        auto& q = sycl_engine.q;

        // Pull frequently-used scalars from shared-USM ONCE per loop (or outside)
        const size_t NX = *sycl_engine.d_nx;
        const size_t NY = *sycl_engine.d_ny;

        // Start looping through time steps
        //####################################

        while (t < t_final - 1e-15) 
        {

            // sample sources at midpoint time
            const auto t_sample = t + 0.5 * dt;

            // Cache device pointers & constants for kernel capture
            double* d_u = sycl_engine.d_u;
            double* d_un = sycl_engine.d_un;
            double* d_alpha = sycl_engine.d_alpha;    // may be nullptr -> use 1.0 below
            const Source* d_src = sycl_engine.d_sources;
            const auto source_count = (sycl_engine.d_num_sources ? *sycl_engine.d_num_sources : 0);

            const auto invdx2 = *sycl_engine.d_invdx2;
            const auto invdy2 = *sycl_engine.d_invdy2;
            const auto dx = *sycl_engine.d_dx;
            const auto dy = *sycl_engine.d_dy;

            // ---- main interior update (1..NY-2, 1..NX-2)
            q.parallel_for(sycl::range<2>(NY - 2, NX - 2),
                        [=](sycl::id<2> ij) {
                const auto j = ij[0] + 1;
                const auto i = ij[1] + 1;
                const auto idx = j*NX + i;

                const auto x = i * dx;
                const auto y = j * dy;

                const auto uij = d_u[idx];
                const auto lap =    (d_u[idx + 1] - 2.0*uij + d_u[idx - 1]) * invdx2 
                                  + (d_u[idx + NX] - 2.0*uij + d_u[idx - NX]) * invdy2;

                // Aggregate sources
                auto source_accumulator = 0.0;
                auto constant = -1.0;

                for (std::size_t k = 0; k < source_count; k++) 
                {
                    const auto source = d_src[k];
                    const auto val = source_value_at_device(source, t_sample, x, y, dt, dx, dy);
                    if (source.temporal_kind == Source::TemporalKind::Rate) 
                    {
                        source_accumulator += val;
                    } 
                    else if (source.temporal_kind == Source::TemporalKind::Constant) 
                    {
                        constant = sycl::fmax(constant, val);
                    } 
                    else 
                    { // Impulse
                        // modeled as an integrated impulse over this dt
                        source_accumulator += val; // val already active only in the impulse window
                    }
                }

                const auto aij = (d_alpha ? d_alpha[idx] : 1.0);


                // If a constant, just override with this value
                if(constant > 0.0)
                {
                    d_un[idx] = constant;
                }
                // If not, the value at the next time step is the 
                // value at this time step + thermal diffusivity * dt * \Delta^2u 
                //                         + thermal diffusivity * dt * S
                else
                {
                    d_un[idx] = uij + aij * dt * (lap + source_accumulator);
                }

                // Alternate ternary:
                //d_un[idx] = (constant > 0.0)
                //    ? constant
                //   : (uij + aij * dt * (lap + Sacc));
            }).wait();

            // Zero boundaries
            sycl_engine.dirichlet_boundaries();

            // ---- swap device buffers for next step
            sycl_engine.swap_buffers();

            // Increment time and step counter
            t += dt;
            step++;

            // Save grid to file (at time t)
            if (step % snapshot_every == 0 || t >= t_final - 1e-15) 
            {
                // Copy u from device
                sycl_engine.download_grid(model_grid);

                if(queue_output)
                {      
                    writer.enqueue(prefix, outdir, t, step, model_grid);
                }
                else
                {
                    writer.grid_to_csv(prefix, outdir, t, step, model_grid);
                }

                std::cerr << "t=" << t << " (step " << step << ")" << ", L2=" << Heat::rss(model_grid.u) << "\n";
            }
        }
    }


};


#endif