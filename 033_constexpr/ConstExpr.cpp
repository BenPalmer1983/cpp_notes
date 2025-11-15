
#include <iostream>
#include <array>
#include <string>

// ================== Function prototypes ==================
void print_array(const std::array<int, 5>& a);
void note(const std::string& msg, const bool verbose);


// Must be defined before used - constexpr

constexpr int square(int x)
{
    return x * x;
}

constexpr int min_ce(int a, int b)
{
    return (a < b) ? a : b;
}


constexpr int fib(int n)
{
    // Basic, small illustrative version (no memoization)
    return (n <= 1) ? n : (fib(n - 1) + fib(n - 2));
}


int main(int argc, char* argv[])
{

    std::cout << "const variables - promise not to change this value, enforced by the compiler" << std::endl;
    std::cout << "constexpr variables - evaluated at compile time, read only memory, unlikely to be corrupted, better performance" << std::endl;
    std::cout << "(see A Tour of C++, Bjarne Stroustrup.)" << std::endl;

    // Verbose flag
    bool verbose = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg {argv[i]};
        if (arg == "-v" || arg == "--verbose") { verbose = true; }
    }

    // 1) constexpr variables — compile-time constants
    {
        std::cout << "constexpr variables (compile-time constants)." << std::endl;

        constexpr int a {10};            // must be initializable at compile time
        constexpr int b {20};
        constexpr int c = a + b;         // still compile-time

        std::cout << "a: " << a << ", b: " << b << ", c=a+b: " << c << "\n" << std::endl;

        // Note: constexpr implies const, but not every const is constexpr.
        note("constexpr variables are also const, but 'const' alone may not be a constant expression.", verbose);

        std::cout << std::endl;
    }

    // 2) constexpr functions — usable at compile time *and* run time
    {
        std::cout << "constexpr functions (can run at compile time or runtime)." << std::endl;

        constexpr int four_sq = square(4);      // evaluated at compile time
        std::cout << "square(4) [constexpr]: " << four_sq << std::endl;

        int x {7};                               // runtime value
        int xsq = square(x);                     // may be runtime (depends on 'x' being known at compile time)
        std::cout << "square(7)   [runtime]:    " << xsq << "\n" << std::endl;

        note("Same function can be folded at compile time if all inputs are constant expressions.", verbose);

        std::cout << std::endl;
    }

    // 3) constexpr with conditional logic
    {
        std::cout << "constexpr with conditional logic (no dynamic features inside)." << std::endl;

        constexpr int m = min_ce(12, 5);
        std::cout << "min_ce(12,5): " << m << "\n" << std::endl;

        note("You can use if/?: in constexpr functions; no I/O, no heap, no non-constexpr globals.", verbose);

        std::cout << std::endl;
    }

    // 4) constexpr and fixed-size arrays (std::array)
    {
        std::cout << "Use constexpr values as array sizes (std::array)." << std::endl;

        constexpr int n {5};
        std::array<int, n> arr {1,2,3,4,5};

        std::cout << "arr: ";
        print_array(arr);
        std::cout << "\n" << std::endl;

        note("std::array size must be a compile-time constant; constexpr works perfectly.", verbose);

        std::cout << std::endl;
    }

    // 5) A small constexpr algorithm (Fibonacci)
    {
        std::cout << "constexpr Fibonacci for small n (illustration)." << std::endl;

        constexpr int f5 = fib(5);   // compile-time
        std::cout << "fib(5)  [constexpr]: " << f5 << std::endl;

        int n_rt {8};
        int f8 = fib(n_rt);          // runtime, because n_rt is not a constant expression
        std::cout << "fib(8)  [runtime]:   " << f8 << "\n" << std::endl;

        note("Avoid deep recursion at compile time — keep constexpr algorithms small and simple.", verbose);

        std::cout << std::endl;
    }

    // 6) constexpr vs const — quick contrast
    {
        std::cout << "constexpr vs const." << std::endl;

        const int may_be_runtime = [](){ return 42; }(); // not a constant expression (calls a runtime lambda)
        // std::array<int, may_be_runtime> bad {};       // would fail: size is not a constant expression

        constexpr int truly_constexpr = 42;               // OK: compile-time
        std::array<int, truly_constexpr> ok {};           // OK

        std::cout << "const may_be_runtime = 42 (runtime init), constexpr truly_constexpr = 42 (compile-time)." << std::endl;
        std::cout << "OK to use constexpr as non-type template args (e.g. std::array size)." << "\n" << std::endl;

        note("Rule of thumb: use constexpr when you *need* a true compile-time constant.", verbose);

        std::cout << std::endl;
    }

    return 0;
}

// ================== Function definitions ==================

void print_array(const std::array<int, 5>& a)
{
    std::cout << "[";
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        std::cout << a[i];
        if (i + 1 < a.size()) { std::cout << ", "; }
    }
    std::cout << "]";
}

void note(const std::string& msg, const bool verbose)
{
    if (verbose)
    {
        std::cout << "    [note] " << msg << std::endl;
    }
}





