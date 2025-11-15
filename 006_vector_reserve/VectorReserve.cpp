// =========================================================
//  Lesson: std::vector in C++ (no loops)
//  Demonstrates creation, modification, and inspection
//  Includes: .at(), .pop_back(), .erase(), .clear(), .insert()
// =========================================================

/*
 * std::vector
 * ===========
 * Contiguous in memory: Yes
 * Random access: O(1)
 * push_back / emplace_back: Amortized O(1)     (averaged time complextity over sequence of operations)
 * pop_back: O(1)
 * insert (any position): O(n) — shifts elements
 * erase (any position): O(n) — shifts elements
 * Iterator invalidation: All iterators invalidated on reallocation or insert/erase
 * Cache locality: Excellent — sequential memory access
 * Memory overhead: Minimal (just capacity + size)
 * Size query: O(1) — via .size()
 * Capacity management: May reallocate (doubles capacity on overflow)
 * Suitable for: Frequent random access, cache-sensitive loops, stable size
 */


#include <iostream>
#include <string>
#include <vector>
#include <random>

// Prototype
void inspect_vector(const std::vector<int>& v);



int main(int argc, char* argv[])
{
    // Verbose flag
    bool verbose = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg {argv[i]};
        if (arg == "-v" || arg == "--verbose") { verbose = true; }
    }



    // Random number generator
    std::mt19937_64 rng(123456789ULL);
    std::uniform_real_distribution<double> dist(0.0, 1.0);    // [0.0, 1.0)


    // -----------------------------------------------------
    // 1. Reserve
    // -----------------------------------------------------

    {
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "=============================================" << std::endl;
        std::cout << "Reserve space." << std::endl;
        std::cout << "=============================================" << std::endl;

        auto N = std::size_t(1000);
        std::vector<double> my_vector {};
        my_vector.reserve(N);
        
        for(auto i = 0; i< N; ++i)
        {
            my_vector.emplace_back(dist(rng));
        }


        std::cout << "Reserve space." << std::endl;
        std::cout << "Size of vector:" << my_vector.size() << std::endl;

    }

    // -----------------------------------------------------
    // 2. Reserve
    // -----------------------------------------------------

    {
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "=============================================" << std::endl;
        std::cout << "Reserve space." << std::endl;
        std::cout << "=============================================" << std::endl;

        auto N = std::size_t(1000);
        std::vector<double> my_vector {};
        my_vector.reserve(N);


        std::cout << "Before" << std::endl;
        std::cout << "  Size of vector:       " << my_vector.size() << std::endl;
        std::cout << "  Capacity of vector:   " << my_vector.capacity() << std::endl;
        
        for(auto i = 0; i< N; ++i)
        {
            my_vector.emplace_back(dist(rng));
        }

        std::cout << "After" << std::endl;
        std::cout << "  Size of vector:       " << my_vector.size() << std::endl;
        std::cout << "  Capacity of vector:   " << my_vector.capacity() << std::endl;

    }

    // -----------------------------------------------------
    // 3. Reserve
    // -----------------------------------------------------

    {
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "=============================================" << std::endl;
        std::cout << "Reserve space." << std::endl;
        std::cout << "=============================================" << std::endl;

        auto M = std::size_t(1000);
        auto N = std::size_t(100);
        std::vector<double> my_vector {};
        my_vector.reserve(M);


        std::cout << "Before" << std::endl;
        std::cout << "  Size of vector:       " << my_vector.size() << std::endl;
        std::cout << "  Capacity of vector:   " << my_vector.capacity() << std::endl;
        
        for(auto i = 0; i< N; ++i)
        {
            my_vector.emplace_back(dist(rng));
        }

        std::cout << "After" << std::endl;
        std::cout << "  Size of vector:       " << my_vector.size() << std::endl;
        std::cout << "  Capacity of vector:   " << my_vector.capacity() << std::endl;

        my_vector.shrink_to_fit();

        std::cout << "After" << std::endl;
        std::cout << "  Size of vector:       " << my_vector.size() << std::endl;
        std::cout << "  Capacity of vector:   " << my_vector.capacity() << std::endl;

    }



    // -----------------------------------------------------
    // End of program
    // -----------------------------------------------------
    std::cout << "End of vector reserve tutorial." << std::endl;
    return 0;
}


// =========================================================
// Definition of inspect_vector (no loops)
// =========================================================

// Pass-by-reference: we see the same vector object (no copy)
void inspect_vector(const std::vector<int>& v)
{
    std::cout << "[inspect_vector]\n";
    std::cout << "  address of v (the vector object) : " << &v << '\n';
    std::cout << "  v.size()                          : " << v.size() << '\n';

    // Cast v.data() to void* pointer (generic memory address)
    // and promise not to modify data through pointer (const)
    std::cout << "  v.data() (buffer start)           : "
              << static_cast<const void*>(v.data()) << '\n';

    // Show a few representative elements (no loop)
    if (!v.empty())
    {
        std::cout << "  front() = " << v.front() << '\n';
        if (v.size() > 1) std::cout << "  v[1]    = " << v[1] << '\n';
        if (v.size() > 2) std::cout << "  v[2]    = " << v[2] << '\n';
        std::cout << "  back()  = " << v.back() << '\n';
    }
    else
    {
        std::cout << "  (vector is empty)\n";
    }

    std::cout << '\n';
}
