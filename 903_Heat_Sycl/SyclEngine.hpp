#ifndef SYCLENGINE_HPP
#define SYCLENGINE_HPP

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



struct SyclEngine 
{
    sycl::queue q{};

    size_t nx {};
    size_t ny {};
    size_t num_sources {};

    size_t* d_nx {nullptr};
    size_t* d_ny {nullptr};
    double* d_dx {nullptr};
    double* d_dy {nullptr};
    double* d_length_x {nullptr};
    double* d_length_y {nullptr};
    double* d_invdx2 {nullptr};
    double* d_invdy2 {nullptr};

    double* d_u {nullptr};
    double* d_un {nullptr};
    double* d_alpha {nullptr};

    Source* d_sources {nullptr};
    size_t* d_num_sources {nullptr};


    // Constructor - save attributes and call allocate
    SyclEngine(const std::string& device, size_t nx_in, size_t ny_in, size_t num_sources_in) : nx(nx_in), ny(ny_in), num_sources(num_sources_in)
    {
        // Make queue and allocate memory on device
        _make_queue(device);
        _allocate();
    }
    ~SyclEngine() { _cleanup(); }






    // host -> device
    void upload_grid(const Grid& model_grid, const std::vector<Source>& sources)  
    { 
        // Check dimensions ok or throw error
        _check_dims(model_grid); 

        const auto n = model_grid.nx * model_grid.ny;

        *d_nx = model_grid.nx;
        *d_ny = model_grid.ny;
        *d_dx = model_grid.dx;
        *d_dy = model_grid.dy;

        *d_length_x = model_grid.length_x;
        *d_length_x = model_grid.length_y;
        *d_invdx2 = model_grid.invdx2;
        *d_invdy2 = model_grid.invdy2;

        // Copy grids (u, un, thermal diffusivity)
        q.memcpy(d_u,  model_grid.u.data(),  sizeof(double)*n).wait(); 
        q.memcpy(d_un,  model_grid.un.data(),  sizeof(double)*n).wait(); 
        q.memcpy(d_alpha,  model_grid.alpha.data(),  sizeof(double)*n).wait(); 
    
        // Store number of sources locally and on device
        num_sources = sources.size();
        *d_num_sources = num_sources;
        q.memcpy(d_sources, sources.data(), sizeof(Source) * num_sources).wait();
        

    }
    
    // device -> host
    void download_grid(Grid& model_grid)
    {
        _check_dims(model_grid);

        const auto n = model_grid.nx * model_grid.ny;

        q.memcpy(model_grid.u.data(),  d_u,  sizeof(double)*n).wait();
        q.memcpy(model_grid.un.data(), d_un, sizeof(double)*n).wait();
    }

    // Zero boundaries
    void dirichlet_boundaries()
    {
        const auto NX = *d_nx;  
        const auto NY = *d_ny;
        const auto un = d_un; 

        // Top / bottom rows
        q.parallel_for(sycl::range<1>(NX), [=](sycl::id<1> ii){
            const auto i = ii[0];
            un[0*NX + i] = 0.0;                 // top
            un[(NY - 1)*NX + i] = 0.0;          // bottom
        });

        // Left / right columns
        q.parallel_for(sycl::range<1>(NY), [=](sycl::id<1> jj){
            const auto j = jj[0];
            un[j*NX + 0] = 0.0;                 // left
            un[j*NX + (NX-1)]  = 0.0;           // right
        });

        q.wait();
    }



    // Swap u and un device buffers (cheap pointer swap)
    void swap_buffers() 
    {
        std::swap(d_u, d_un);
    }

    // Size
    size_t size() 
    {
        return nx * ny;
    }


private:

    // Make queue
    void _make_queue(const std::string& device)
    {

        if (device == "cpu") 
        {
            q = sycl::queue{sycl::cpu_selector_v};
        } 
        else if (device == "gpu") 
        {
            q = sycl::queue{sycl::gpu_selector_v};
        } 
        else
        {
            q = sycl::queue{sycl::default_selector_v};
        }

        std::cerr << "Using device: " << q.get_device().get_info<sycl::info::device::name>() << "\n";
    }


    // Allocate memory on the device
    void _allocate() 
    {

        if (nx == 0 || ny == 0) throw std::runtime_error("DeviceGrid: zero dimensions");
        const auto n = nx * ny;

        d_nx = sycl::malloc_shared<size_t>(1, q);
        d_ny = sycl::malloc_shared<size_t>(1, q);
        d_dx = sycl::malloc_shared<double>(1, q);
        d_dy = sycl::malloc_shared<double>(1, q);
        if (!d_nx || !d_ny || !d_dx || !d_dy) throw std::bad_alloc{};

        d_length_x = sycl::malloc_shared<double>(1, q);
        d_length_y = sycl::malloc_shared<double>(1, q);
        d_invdx2 = sycl::malloc_shared<double>(1, q);
        d_invdy2 = sycl::malloc_shared<double>(1, q);
        if (!d_length_x || !d_length_y || !d_invdx2 || !d_invdy2) throw std::bad_alloc{};

        d_u  = sycl::malloc_device<double>(n, q);
        d_un = sycl::malloc_device<double>(n, q);
        d_alpha = sycl::malloc_device<double>(n, q);

        if (!d_u) throw std::bad_alloc{};
        if (!d_un) throw std::bad_alloc{};
        if (!d_alpha) throw std::bad_alloc{};

        d_num_sources = sycl::malloc_shared<size_t>(1, q);
        if (!d_num_sources) throw std::bad_alloc{};

        d_sources = sycl::malloc_device<Source>(num_sources, q);
        if (!d_sources) throw std::bad_alloc{};
        
    }


    // Clean up device
    void _cleanup() 
    {
        if (d_u)  { sycl::free(d_u,  q); d_u  = nullptr; }
        if (d_un) { sycl::free(d_un, q); d_un = nullptr; }
        if (d_u)  { sycl::free(d_u,  q); d_u  = nullptr; }
        if (d_un) { sycl::free(d_un, q); d_un = nullptr; }
        if (d_alpha) { sycl::free(d_alpha, q); d_alpha = nullptr; }
    }

    // Check dimensions
    void _check_dims(const Grid& g) const 
    {
        if (g.nx != nx || g.ny != ny)
        {
            throw std::runtime_error("DeviceGrid: Grid dims mismatch");
        }
        if (g.u.size() != nx * ny || g.un.size() != nx * ny)
        {
            throw std::runtime_error("DeviceGrid: Grid vector sizes mismatch");
        }
    }
    

};



#endif