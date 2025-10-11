#include <iostream>
#include <vector>
#include <string>

// ================== Prototypes ==================
int& good_ref();
int  counter(bool verbose);
void print_vector(const std::vector<int>& v);
void push_back_with_report(std::vector<int>& v, int value, bool verbose);

int main(int argc, char* argv[])
{
    // Verbose flag
    bool verbose = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg {argv[i]};
        if (arg == "-v" || arg == "--verbose") { verbose = true; }
    }

    // 1) Block scope — variables live only inside the braces
    {
        std::cout << "Block scope demo." << std::endl;

        int inside {42};
        std::cout << "inside: " << inside << "\n" << std::endl;

        std::cout << std::endl;
    }
    std::cout << "Outside block: 'inside' no longer exists.\n" << std::endl;

    // 2) Static local variables — persist across calls
    {
        std::cout << "Static local keeps state across calls." << std::endl;

        std::cout << "counter(): " << counter(verbose) << std::endl;
        std::cout << "counter(): " << counter(verbose) << std::endl;
        std::cout << "counter(): " << counter(verbose) << "\n" << std::endl;

        std::cout << std::endl;
    }

    // 3) Returning references — safe vs unsafe
    {
        std::cout << "Return reference to static is safe; local would be unsafe." << std::endl;

        int& r = good_ref();     // refers to a static
        std::cout << "good_ref(): " << r << std::endl;
        r = 777;                 // modify the static through the reference
        std::cout << "good_ref() after change: " << good_ref() << "\n" << std::endl;

        // Example of what NOT to do (uncomment to see compiler error)
        // (see later tutorial on lambdas)
        /*
            int& bad = []() -> int& {
                int x {123};   // (1) x is a local (automatic storage)
                return x;      // (2) returning a reference to x
            }();               // (3) lambda is invoked right here
            // (4) lambda ends, x is destroyed; 'bad' now refers to a dead object
        */


        std::cout << std::endl;
    }

    // 4) Temporaries and const references
    {
        std::cout << "Const reference can extend temporary lifetime." << std::endl;

        const int& cr = 123 + 456; // temporary lives as long as 'cr'
        std::cout << "cr: " << cr << std::endl;

        // int& nr = 10; // <- would not compile: non-const ref cannot bind to temporary
        std::cout << "Non-const reference cannot bind to a temporary.\n" << std::endl;

        std::cout << std::endl;
    }

    // 5) Vector element references & reallocation
    {
        std::cout << "Vector references may break on reallocation." << std::endl;

        std::vector<int> v {1,2,3};

        if (verbose)
        {
            std::cout << "    [before] capacity=" << v.capacity()
                      << " data()=" << static_cast<const void*>(v.data()) << '\n';
        }

        // Get a reference to the first element
        int& first = v[0];
        std::cout << "first(before): " << first << std::endl;

        // Push with reporting (shows capacity/data changes in verbose mode)
        push_back_with_report(v, 4, verbose);

        // This assignment is only safe if reallocation did not occur.
        first = 99;

        std::cout << "v: ";
        print_vector(v);
        std::cout << "\n" << std::endl;

        std::cout << "Note: if capacity grew, old references/iterators are invalid." << "\n" << std::endl;

        std::cout << std::endl;
    }

    return 0;
}

// ================== Definitions ==================

int& good_ref()
{
    static int persistent {100}; // lives for the entire program
    return persistent;
}

int counter(bool verbose)
{
    static int c {};
    c++;

    if (verbose)
    {
        std::cout << "    [counter] c=" << c << " (static persists across calls)\n";
    }
    return c;
}

void print_vector(const std::vector<int>& v)
{
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i];
        if (i + 1 < v.size()) { std::cout << ", "; }
    }
    std::cout << "]";
}

void push_back_with_report(std::vector<int>& v, int value, bool verbose)
{
    const void* before_data = static_cast<const void*>(v.data());
    std::size_t before_cap  = v.capacity();

    v.push_back(value);

    const void* after_data = static_cast<const void*>(v.data());
    std::size_t after_cap  = v.capacity();

    if (verbose)
    {
        std::cout << "    [push_back]\n"
                  << "        value: " << value << '\n'
                  << "        capacity: " << before_cap << " -> " << after_cap << '\n'
                  << "        data():  " << before_data  << " -> " << after_data
                  << (before_data == after_data ? " (no reallocation)\n" : " (REALLOCATED)\n")
                  << std::endl;
    }
}




