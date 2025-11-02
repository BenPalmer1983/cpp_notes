// cuda.cu
#include <iostream>
#include <iomanip>
#include <vector>
#include <cuda_runtime.h>


// CUDA kernel: doubles each element
// camelCase like other CUDA functions
__global__ void doubleVector(double* d_vec, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) 
    {
        d_vec[idx] = 2.0 * d_vec[idx];
    }
}



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

    // Allocate device memory
    double* device_vector;
    cudaMalloc(&device_vector, N * sizeof(double));

    // Copy host -> device
    cudaMemcpy(device_vector, host_vector.data(), N * sizeof(double), cudaMemcpyHostToDevice);

    // Launch kernel
    auto threadsPerBlock = std::size_t(256);
    auto blocks = std::size_t((N + threadsPerBlock - 1) / threadsPerBlock);

    std::cout << "threadsPerBlock:    " << threadsPerBlock << std::endl;
    std::cout << "blocks:             " << blocks << std::endl;
    doubleVector<<<blocks, threadsPerBlock>>>(device_vector, N);

    // Check for kernel launch errors
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) 
    {
        std::cerr << "Kernel launch error: " << cudaGetErrorString(err) << std::endl;
        return -1;
    }

    // Copy device -> host
    cudaMemcpy(host_vector.data(), device_vector, N * sizeof(double), cudaMemcpyDeviceToHost);

    // Wait for GPU to finish
    cudaDeviceSynchronize();

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
    cudaFree(device_vector);

    return 0;
}
