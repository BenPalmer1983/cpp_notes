
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 


int upper_bound(const std::vector<int>& arr, int x) 
{
    // Set upper/lower
    size_t low = 0;
    size_t high = arr.size();
    
    while (low < high) 
    {

        // Mid point between low and high
        size_t mid = low + (high - low) / 2;

        if (arr[mid] <= x)       // If the x > mid point, adjust to look in [mid+1, high]
        {
            low = mid + 1;      
        }
        else
        {
            high = mid;         // If the mid point <= x, adjust to look in [low, mid]
        }
    }

    if(low < arr.size())
    {
        return arr[low];
    }
    else
    {
        return -1;
    }
}


// https://www.youtube.com/watch?v=RK3CEJRaznw
int* upper_bound_pointers(int* first, int* last, int x)
{
    // If not allocated, return last (nullptr)
    if(first == nullptr || last == nullptr || first == last)
    {
        return last;
    }
    while(first != last)
    {
        int* middle = first + (last - first) / 2;
        if(x >= *middle)
        {
            first = middle + 1;
        }
        else
        {
            last = middle;
        }
    }
    return last;
}




int main()
{
    const int SIZE = 1000000;
    const unsigned int SEED = 12345;

    std::vector<int> arr;
    arr.reserve(SIZE);

    std::random_device rd;  // Non-deterministic seed
    std::mt19937 gen(SEED); // Mersenne Twister RNG
    std::uniform_int_distribution<int> dist(0, 5);

    int x {234578};

    for (int i = 0; i < SIZE; i++) 
    {
        arr.push_back(i + dist(gen));
    }

    for(auto i : arr)
    {
        //std::cout << i << std::endl;
    }


    {
        auto start = std::chrono::high_resolution_clock::now();
        int result = upper_bound(arr, x); 
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << result << "     " << elapsed.count() << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        int* result = upper_bound_pointers(arr.data(), arr.data() + arr.size(), x);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << *result << "     " << elapsed.count() << std::endl;
    }

    {
        // Use the standard library
        auto start = std::chrono::high_resolution_clock::now();
        auto result = std::upper_bound(arr.begin(), arr.end(), x);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << *result << "     " << elapsed.count() << std::endl;
    }


    return 0;
}





