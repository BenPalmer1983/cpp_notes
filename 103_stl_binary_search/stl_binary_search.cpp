
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 



bool binary_search(int* first, int* last, int x)
{
    // If not allocated, return last (nullptr)
    if(first == nullptr || last == nullptr || first == last)
    {
        return false;
    }
    while(first != last)
    {
        int* middle = first + (last - first) / 2;
        if(x == *middle)
        {
            return true;
        }
        else if(x >= *middle)
        {
            first = middle + 1;
        }
        else
        {
            last = middle;
        }
    }
    return false;
}




int main()
{
    // Create an array for testing

    const int SIZE = 1000000;
    const unsigned int SEED = 12345;

    std::vector<int> arr;
    arr.reserve(SIZE);

    std::random_device rd;  // Non-deterministic seed
    std::mt19937 gen(SEED); // Mersenne Twister RNG
    std::uniform_int_distribution<int> dist(0, 5);

    int x {234579};

    for (int i = 0; i < SIZE; i++) 
    {
        arr.push_back(i + dist(gen));
    }


    {
        auto start = std::chrono::high_resolution_clock::now();
        auto result = binary_search(arr.begin(), arr.end(), x); 
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << result << "     " << elapsed.count() << std::endl;
    }


    {
        // Use the standard library
        auto start = std::chrono::high_resolution_clock::now();
        auto result = std::binary_search(arr.begin(), arr.end(), x);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << result << "     " << elapsed.count() << std::endl;
    }

    return 0;
}





