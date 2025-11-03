// cuda.cu
#include <iostream>
#include <iomanip>
#include <vector>
#include <sycl/sycl.hpp>




int main(int argc, char** argv)
{
    
    // Read in path to configuration file     
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <size> " << std::endl;
        std::cerr << "       " << argv[0] << " 100 " << std::endl;
        
        return 1;
    }

    const auto vector_size = std::size_t(std::atoi(argv[1]));

    std::vector<double> host_vector = {};

    for(auto i = 0; i<vector_size; i++)
    {
        host_vector.emplace_back(1.0 * i); 
    }

    const auto N = std::size_t(host_vector.size());

    // Print original
    std::cout << "Original: ";
    for (int i = 0; i < N; i++) 
    {
        if(i < 5 || i > (N - 5))
        {
            std::cout << host_vector[i] << " ";
        }
    }
    std::cout << "\n";

    // Create queue
    sycl::queue q = sycl::queue{sycl::gpu_selector_v};
    std::cerr << "Using device: " << q.get_device().get_info<sycl::info::device::name>() << "\n";

    // Allocate memory on device
    double* device_vector = sycl::malloc_device<double>(N, q);

    // Copy host vector to device
    q.memcpy(device_vector,  host_vector.data(),  sizeof(double)*N).wait(); 

    // Double
    q.parallel_for(sycl::range<1>(N), [=](sycl::id<1> ii)
    {
        const auto i = ii[0];
        device_vector[i] = 2.0 * device_vector[i]; 
    });

    // Copy back to host
    q.memcpy(host_vector.data(),  device_vector,  sizeof(double)*N).wait();
    

    // Print result
    std::cout << "Doubled : ";
    for (int i = 0; i < N; i++) 
    {
        if(i < 5 || i > (N - 5))
        {
            std::cout << host_vector[i] << " ";
        }
    }
    std::cout << std::endl;

    // Cleanup
    if (device_vector)  { sycl::free(device_vector,  q); device_vector  = nullptr; }

    return 0;
}
