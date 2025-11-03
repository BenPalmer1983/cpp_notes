// openmp.cpp

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <random>
#include "dgemm.hpp"



// X = k A * B + l C
int main(int argc, char** argv) 
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " rows cols\n";
        return 1;
    }
    
    const int rows = std::atoi(argv[1]);   
    const int cols = std::atoi(argv[2]);  

    // Random number generator
    std::mt19937_64 rng(123456789ULL);
    std::uniform_real_distribution<double> dist(0.0, 1.0);  // [0.0, 1.0)

    // Matrix dimensions:
    // A: rows × cols
    // B: cols × rows 
    // C: rows × rows  
    Dgemm::Matrix A(rows, std::vector<double>(cols, 0.0)); 
    Dgemm::Matrix B(cols, std::vector<double>(rows, 0.0)); 
    Dgemm::Matrix C(rows, std::vector<double>(rows, 0.0)); 

    double k = dist(rng);
    double l = dist(rng);

    // Fill A
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            A[i][j] = dist(rng);
        }
    }

    // Fill B
    for (int i = 0; i < cols; i++) 
    {        
        for (int j = 0; j < rows; j++) 
        {
            B[i][j] = dist(rng);
        }
    }

    // Fill C
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < rows; j++) 
        {
            C[i][j] = dist(rng);
        }
    }

    {
        auto t0 = std::chrono::steady_clock::now();

        Dgemm::Matrix X = Dgemm::dgemm_serial(k, A, B, l, C, rows, cols);
        double expected_value = Dgemm::check_sum(X);

        auto t1 = std::chrono::steady_clock::now();

        double time_setup = std::chrono::duration<double>(t1 - t0).count();

        std::cout << expected_value << "    " << time_setup << std::endl;
    }

    {
        auto t0 = std::chrono::steady_clock::now();

        Dgemm::Matrix X = Dgemm::dgemm_sycl(k, A, B, l, C, rows, cols);
        double expected_value = Dgemm::check_sum(X);

        auto t1 = std::chrono::steady_clock::now();

        double time_setup = std::chrono::duration<double>(t1 - t0).count();

        std::cout << expected_value << "    " << time_setup << std::endl;
    }
    
 

    
    return 0;
}
