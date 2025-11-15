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

    // -----------------------------------------------------
    // 1. Create and inspect an empty vector
    // -----------------------------------------------------

    std::cout << "Create an empty vector of doubles." << std::endl;
    std::vector<double> v;

    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Empty? " << std::boolalpha << v.empty() << "\n" << std::endl;   // std::boolalpha prints true/false instead of 1/0


    // -----------------------------------------------------
    // 2. Add elements (initializer list instead of a loop)
    // -----------------------------------------------------

    std::cout << "Add 5 elements using an initializer list." << std::endl;
    v = {1.1, 2.2, 3.3, 4.4, 5.5};

    std::cout << "Size after adding: " << v.size() << std::endl;

    // Print a few representative values (no loop)
    if (!v.empty())
    {
        std::cout << "First element: " << v[0] << std::endl;
        if (v.size() > 1) std::cout << "Second element (via .at): " << v.at(1) << std::endl;
        std::cout << "Last element: " << v.back() << "\n" << std::endl;
    }
    else
    {
        std::cout << "(vector is empty)\n" << std::endl;
    }


    // -----------------------------------------------------
    // 3. Access elements: operator[] and .at()
    // -----------------------------------------------------

    std::cout << "Accessing elements:" << std::endl;
    if (v.size() >= 2)
    {
        std::cout << "v[0]: " << v[0] << std::endl;
        std::cout << "v.at(1): " << v.at(1) << "  (bounds-checked)\n" << std::endl;
    }
    else
    {
        std::cout << "Not enough elements to demonstrate access.\n" << std::endl;
    }

    // Uncomment to test exception
    // std::cout << v.at(99); // Throws std::out_of_range


    // -----------------------------------------------------
    // 4. Modify elements
    // -----------------------------------------------------

    if (v.size() > 2)
    {
        std::cout << "Modify v[2] to 99.9." << std::endl;
        v[2] = 99.9;

        std::cout << "Check modified positions (no loop):" << std::endl;
        std::cout << "v[0] = " << v[0] << std::endl;
        std::cout << "v[1] = " << v[1] << std::endl;
        std::cout << "v[2] = " << v[2] << "\n" << std::endl;
    }


    // -----------------------------------------------------
    // 5. pop_back() — remove last element
    // -----------------------------------------------------

    if (!v.empty())
    {
        std::cout << "Remove last element with pop_back()." << std::endl;
        v.pop_back();

        std::cout << "Size after pop_back(): " << v.size() << std::endl;
        if (!v.empty())
        {
            std::cout << "New last element: " << v.back() << "\n" << std::endl;
        }
        else
        {
            std::cout << "(vector is now empty)\n" << std::endl;
        }
    }


    // -----------------------------------------------------
    // 6. insert() — add element in the middle
    // -----------------------------------------------------

    if (v.size() >= 3)
    {
        std::cout << "Insert 123.456 at position 2." << std::endl;
        v.insert(v.begin() + 2, 123.456);

        // Show a few elements around the insertion point
        std::cout << "After insert (selected indices):" << std::endl;
        std::cout << "v[1] = " << v[1] << std::endl;
        std::cout << "v[2] = " << v[2] << "  (inserted)" << std::endl;
        if (v.size() > 3) std::cout << "v[3] = " << v[3] << "\n" << std::endl;
        else std::cout << "\n";
    }


    // -----------------------------------------------------
    // 7. erase() — remove an element at a position
    // -----------------------------------------------------

    if (v.size() > 1)
    {
        std::cout << "Erase element at position 1." << std::endl;
        v.erase(v.begin() + 1);

        std::cout << "After erase (selected indices):" << std::endl;
        std::cout << "Size: " << v.size() << std::endl;
        if (!v.empty())
        {
            std::cout << "v[0] = " << v[0] << std::endl;
            if (v.size() > 1) std::cout << "v[1] = " << v[1] << "\n" << std::endl;
            else std::cout << "\n";
        }
        else
        {
            std::cout << "(vector is empty)\n" << std::endl;
        }
    }


    // -----------------------------------------------------
    // 8. clear() — remove all elements
    // -----------------------------------------------------

    std::cout << "Clear all elements with clear()." << std::endl;
    v.clear();

    std::cout << "Size after clear(): " << v.size() << std::endl;
    std::cout << "Empty? " << std::boolalpha << v.empty() << "\n" << std::endl;


    // -----------------------------------------------------
    // 9. Vector initialized with values (ints)
    // -----------------------------------------------------

    std::cout << "Create a new vector with initial values." << std::endl;
    std::vector<int> numbers {10, 20, 30, 40, 50};

    std::cout << "numbers size: " << numbers.size() << std::endl;
    std::cout << "First: " << numbers.front() << ", Last: " << numbers.back() << "\n" << std::endl;

    if (verbose)
    {
        inspect_vector(numbers);
    }


    // -----------------------------------------------------
    // 10. Insert and erase on integer vector
    // -----------------------------------------------------

    if (numbers.size() >= 3)
    {
        numbers.insert(numbers.begin() + 2, 99);
        std::cout << "After insert at index 2: numbers[2] = " << numbers[2] << std::endl;
        std::cout << "Size: " << numbers.size() << std::endl;

        if (numbers.size() > 4)
        {
            numbers.erase(numbers.begin() + 4);
            std::cout << "After erase at index 4: ";
            std::cout << "Size: " << numbers.size() << std::endl;
            std::cout << "numbers[0] = " << numbers[0] << ", numbers.back() = " << numbers.back() << "\n" << std::endl;
        }
        else
        {
            std::cout << "(not enough elements to erase index 4)\n" << std::endl;
        }
    }

    if (verbose)
    {
        inspect_vector(numbers);
    }

    // -----------------------------------------------------
    // End of program
    // -----------------------------------------------------
    std::cout << "End of vector demonstration." << std::endl;
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
