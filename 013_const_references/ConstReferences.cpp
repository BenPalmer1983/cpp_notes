#include <iostream>
#include <vector>
#include <string>

// ================== Prototypes ==================
int  sum_vector(const std::vector<int>& v, bool verbose);
void set_all(std::vector<int>& v, int value, bool verbose);
int& front_of(std::vector<int>& v);
int  front_of(const std::vector<int>& v);
void print_vector(const std::vector<int>& v);
void note(const std::string& msg, bool verbose);
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

    // 1) const reference — no copy, no mutation
    // Sums
    {
        std::cout << "1) Sum via const reference (no copy)." << std::endl;
        std::vector<int> v {1,2,3,4};

        int s = sum_vector(v, verbose);
        std::cout << "Sum: " << s << "\n" << std::endl;

        std::cout << std::endl;
        std::cout << std::endl;
    }

    // 2) non-const reference — modify in place
    {
        std::cout << "2) Modify via non-const reference (in-place)." << std::endl;

        std::vector<int> v {7,7,7};
        std::cout << "Before: "; print_vector(v); std::cout << std::endl;

        set_all(v, 42, verbose);

        std::cout << "After:  "; print_vector(v); std::cout << "\n" << std::endl;

        std::cout << std::endl;
        std::cout << std::endl;
    }

    // 3) Overload on constness — reference return vs value return
    {
        std::cout << "3) Overload on constness (int& vs int)." << std::endl;

        std::vector<int> v {9,8,7};

        int& r = front_of(v);      // non-const overload -> modifiable reference
        r = 123;                   // modifies v[0]
        note("Modified first element through non-const reference.", verbose);
        if(verbose) std::cout << "v[0] " << v[0] << " at " << static_cast<const void*>(&v[0]) << "  (modified by changing r)" << std::endl;
        if(verbose) std::cout << "r    " << r << " at " << static_cast<const void*>(&r) << std::endl;
        std::cout << std::endl;

        const std::vector<int>& cv = v;
        int copy = front_of(cv);   // const overload -> returns by value (copy)
        note("Const overload returns a copy; modifying it won't affect vector.", verbose);

        std::cout << "v: "; print_vector(v); std::cout << std::endl;
        std::cout << "copy of front: " << copy << "\n" << std::endl;
        if(verbose) std::cout << "v[0] " << v[0] << " at " << static_cast<const void*>(&v[0]) << std::endl;
        if(verbose) std::cout << "copy " << copy << " at " << static_cast<const void*>(&copy) << std::endl;
        std::cout << std::endl;

        copy = 321;
        std::cout << "v: "; print_vector(v); std::cout << "  (not modified by changing copy)" << std::endl;
        std::cout << "copy of front: " << copy << "\n" << std::endl;


        std::cout << std::endl;
        std::cout << std::endl;
    }

    // 4) Attempt to modify through const ref (won't compile)
    {
        std::cout << "4) Const reference prevents mutation." << std::endl;

        const std::vector<int> v {1,2,3};
        print_vector(v); std::cout << std::endl;
        // v[0] = 99; // <- uncomment to see compile error
        std::cout << "Read-only operations are OK.\n" << std::endl;

        std::cout << std::endl;
        std::cout << std::endl;
    }

    return 0;
}

// ================== Definitions ==================

int sum_vector(const std::vector<int>& v, const bool verbose)
{
    int s {};
    for (int x : v) { s += x; }

    if (verbose)
    {
        std::cout << "    [sum_vector]\n";
        std::cout << "        address of v (vector object): " << &v << '\n';
        std::cout << "        size/capacity: " << v.size() << "/" << v.capacity() << '\n';
        std::cout << "        data() (buffer start): " << static_cast<const void*>(v.data()) << "\n\n";
    }
    return s;
}

void set_all(std::vector<int>& v, int value, const bool verbose)
{

    if (verbose) inspect_vector(v);

    for (auto& x : v) { x = value; }

    if (verbose) inspect_vector(v);
}

// Return first element of v (reference, v mutable)
int& front_of(std::vector<int>& v)       
{ 
    return v.front(); 
}

// Return first element of v (copy, v immutable)
int front_of(const std::vector<int>& v) 
{ 
    return v.front(); 
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

void note(const std::string& msg, const bool verbose)
{
    if (verbose)
    {
        std::cout << "    [note] " << msg << std::endl;
    }
}


// Pass-by-reference: we see the same vector object (no copy)
void inspect_vector(const std::vector<int>& v)
{
    std::cout << "[inspect_vector]\n";
    std::cout << "  address of v (the vector object) : " << &v << '\n';
    std::cout << "  v.size()                          : " << v.size() << '\n';

    // Cast v.data() to void* pointer (generic memory address) and promise not to modify data through pointer (const)
    std::cout << "  v.data() (buffer start)           : " << static_cast<const void*>(v.data()) << '\n';

    for (std::size_t i = 0; i < v.size(); i++)
    {
        std::cout << "    v[" << i << "] at " << static_cast<const void*>(&v[i])
                  << " = " << v[i] << '\n';
    }
    std::cout << '\n';
}


