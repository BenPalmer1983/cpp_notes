#include <iostream>
#include <vector>
#include <string>

//
// Function prototypes (so we can define them after main)
//
void modify_by_value(std::vector<int> v);
void modify_in_place(std::vector<int>& v, bool verbose);
void print_vector(const std::vector<int>& v);
std::vector<int> create_vector(std::size_t n, int start);
void inspect_vector(const std::vector<int>& v, bool verbose);


// Main entry point into program
int main(int argc, char* argv[])
{

    // Option to run with Verbose
    bool verbose = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg {argv[i]};
        if (arg == "-v" || arg == "--verbose")
        {
            verbose = true;
        }
    }


    // 1) Pass by value — original is unchanged
    {
        std::cout << "Pass vector by value (copy)." << std::endl;

        std::vector<int> numbers {1,2,3};
        std::cout << "Original size (before): " << numbers.size() << std::endl;

        inspect_vector(numbers, verbose);
        modify_by_value(numbers);   // works on a copy

        std::cout << "Original size (after):  " << numbers.size() << "\n" << std::endl;
        inspect_vector(numbers, verbose);

        std::cout << std::endl;
    }

    // 2) Pass by reference — modify the caller's vector
    {
        std::cout << "Pass vector by reference (modifies original)." << std::endl;

        std::vector<int> numbers {10,20,30};
        std::cout << "Size (before): " << numbers.size() << std::endl;
        inspect_vector(numbers, verbose);

        modify_in_place(numbers, verbose);   // modifies the same object
        std::cout << "Size (after):  " << numbers.size() << std::endl;
        inspect_vector(numbers, verbose);

        std::cout << "Contents: ";
        print_vector(numbers);
        std::cout << "\n" << std::endl;

        std::cout << std::endl;
    }

    // 3) const reference — efficient read-only access
    {
        std::cout << "Use const reference for read-only functions." << std::endl;

        std::vector<int> data {5,4,3,2,1};
        std::cout << "Vector: ";
        print_vector(data);

        // print_vector takes const std::vector<int>& so no copy is made
        std::cout << "\n" << std::endl;

        std::cout << std::endl;
    }

    // 4) Returning vectors from functions
    {
        std::cout << "Return a new vector from a function." << std::endl;

        std::vector<int> seq = create_vector(5, 100); // 100,101,102,103,104

        std::cout << "New vector: ";
        print_vector(seq);
        std::cout << "\n" << std::endl;

        std::cout << std::endl;
    }

    return 0;
}


// ================== Function definitions ==================

void modify_by_value(std::vector<int> v)
{
    std::cout << "  Inside modify_by_value: push_back(99)." << std::endl;
    v.push_back(99);
    std::cout << "  Copy size: " << v.size() << std::endl;
}

void modify_in_place(std::vector<int>& v, bool verbose)
{
    std::cout << "  Inside modify_in_place: push_back(40), push_back(50)." << std::endl;
    v.push_back(40);
    v.push_back(50);
    std::cout << "  Same object size: " << v.size() << std::endl;

    inspect_vector(v, verbose);
}

void print_vector(const std::vector<int>& v)
{
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i];
        if (i + 1 < v.size()) { std::cout << ", "; }
    }
    std::cout << "]";
}

std::vector<int> create_vector(std::size_t n, int start)
{
    std::vector<int> out;
    out.reserve(n);
    for (std::size_t i = 0; i < n; ++i)
    {
        out.push_back(start + static_cast<int>(i));
    }
    return out; // Return Value Optimization (RVO) usually eliminates copies
}



// Pass-by-reference (const): we see the same vector object (no copy)
void inspect_vector(const std::vector<int>& v, bool verbose)
{
    if (!verbose) { return; }

    std::cout << "    [inspect_vector]\n";
    std::cout << "        address of v (vector object)      : " << &v << '\n';
    std::cout << "        v.size()                           : " << v.size() << '\n';
    std::cout << "        v.capacity()                       : " << v.capacity() << '\n';
    std::cout << "        v.data() (buffer start)            : "
              << static_cast<const void*>(v.data()) << '\n';

    if (!v.empty())
    {
        for (std::size_t i = 0; i < v.size(); ++i)
        {
            std::cout << "        v[" << i << "] at "
                      << static_cast<const void*>(&v[i])
                      << " = " << v[i] << '\n';
        }
    }
    std::cout << std::endl;
}
