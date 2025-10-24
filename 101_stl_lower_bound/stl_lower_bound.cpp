
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 


// Find the lowest number in arr that is >= x
int lower_bound(const std::vector<int>& arr, int x) 
{
    if (arr.empty()) return -1; 

    // Set upper/lower
    size_t low = 0;
    size_t high = arr.size() - 1;
    
    while (low != high) 
    {
        // Mid point between low and high
        size_t mid = low + (high - low) / 2;

        if (arr[mid] < x)    // If the mid point < x, adjust to look in [mid+1, high]
        {
            low = mid + 1;   
        }
        else                 // If mid point >= x, look in [low, mid]
        {
            high = mid;    
        }
    }
    return arr[low];         // Return
}


// https://www.youtube.com/watch?v=RK3CEJRaznw
int* lower_bound_pointers(int* first, int* last, int x)
{
    if(first == nullptr || last == nullptr || first == last)
    {
        return last;
    }
    while(first != last)
    {
        int* middle = first + (last - first) / 2;
        if(*middle < x)
        {
            first = middle + 1;
        }
        else
        {
            last = middle;
        }
    }
    return first;
}




int main()
{
    const int SIZE = 1000000;
    const int MIN_VAL = 1;
    const int MAX_VAL = 2000000000;
    const unsigned int SEED = 12345;

    std::vector<int> arr;
    arr.reserve(SIZE);

    std::random_device rd;  // Non-deterministic seed
    std::mt19937 gen(SEED); // Mersenne Twister RNG
    std::uniform_int_distribution<int> dist(MIN_VAL, MAX_VAL);

    int x {212};

    for (int i = 0; i < SIZE; i++) 
    {
        arr.push_back(dist(gen));
    }


    {
        auto start = std::chrono::high_resolution_clock::now();
        int result = lower_bound(arr, x); 
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << result << "     " << elapsed.count() << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        int* result = lower_bound_pointers(arr.data(), arr.data() + arr.size(), x);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << *result << "     " << elapsed.count() << std::endl;
    }

    {
        // Use the standard library
        auto start = std::chrono::high_resolution_clock::now();
        auto result = std::lower_bound(arr.begin(), arr.end(), x);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << *result << "     " << elapsed.count() << std::endl;
    }


    return 0;
}





