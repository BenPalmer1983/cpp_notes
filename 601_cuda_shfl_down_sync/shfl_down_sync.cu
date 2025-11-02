#include <iostream>
#include <cuda_runtime.h>

#define CUDA_CHECK(call) \
    do { \
        cudaError_t err = call; \
        if (err != cudaSuccess) \
        { \
            std::cerr << "CUDA error: " << cudaGetErrorString(err) \
                      << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
            std::exit(1); \
        } \
    } while(0)

// Kernel: demonstrate __shfl_down_sync
__global__ void shflTutorial1()
{
    int lane = threadIdx.x;  // 0 to 31
    double val = lane;       // Each thread starts with its lane ID

    printf("Thread %2d: initial val = %.0f\n", lane, val);

    if (lane == 0) 
    {
        printf("############################################################\n");
    }

    // Warp reduction using shuffle
    for (int offset = 16; offset > 0; offset >>= 1) 
    {

        double other = __shfl_down_sync(0xffffffff, val, offset);

        val += other;
        // Optional: print intermediate steps
        printf("  offset=%2d, thread %2d += from %2d → val = %.0f\n",
                offset, lane, lane + offset, val);
                    
        if (lane == 0) 
        {
            printf("Partial sum = %.0f \n\n", val);
        }
    }

    // Only thread 0 has the full sum
    if (lane == 0) 
    {
        printf("\nFINAL: Warp sum = %.0f (expected: 64)\n", val);
    }
}


__global__ void shflTutorial2()
{
    int lane = threadIdx.x;  // 0 to 31
    double val = 2.0;       // Each thread starts with its lane ID

    printf("Thread %2d: initial val = %.0f\n", lane, val);

    if (lane == 0) 
    {
        printf("############################################################\n");
    }

    // Warp reduction using shuffle
    for (int offset = 16; offset > 0; offset >>= 1) 
    {

        double other = __shfl_down_sync(0xffffffff, val, offset);

        val += other;
        // Optional: print intermediate steps
        printf("  offset=%2d, thread %2d += from %2d → val = %.0f\n",
                offset, lane, lane + offset, val);
                    
        if (lane == 0) 
        {
            printf("Partial sum = %.0f \n\n", val);
        }
    }

    // Only thread 0 has the full sum
    if (lane == 0) 
    {
        printf("\nFINAL: Warp sum = %.0f (expected: 496)\n", val);
    }
}

int main()
{

    std::cout << "Launching 1 warp (32 threads)..." << std::endl;
    std::cout << std::endl;
    
    shflTutorial1<<<1, 32>>>();
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    std::cout << std::endl;
    std::cout << std::endl;

    shflTutorial2<<<1, 32>>>();
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    std::cout << std::endl;
    std::cout << "Done." << std::endl;
    return 0;
}