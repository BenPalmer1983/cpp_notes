// =========================================================
//  References, rvalues, move semantics, vectors & arrays
// =========================================================

#include <iostream>
#include <string>
#include <vector>
#include <utility>  // for std::move

// Pass-by-reference: we see the same vector object (no copy)
void inspect_vector(std::vector<int>& v)
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

// Pass a 3x3 array by reference (no decay to pointer)
void matrix_function(const double (&matrix)[3][3])
{
    std::cout << "[matrix_function]\n";
    std::cout << "  address of matrix (3x3 array)     : " << &matrix << '\n';
    std::cout << "  matrix[1][2]                      : " << matrix[1][2] << "\n\n";
}

int main(int /*argc*/, char* /*argv*/[])
{
    // -----------------------------------------------------
    // lvalues and rvalues, and references
    // -----------------------------------------------------
    int x = 10;                  // x is an lvalue; 10 is an rvalue
    std::cout << "x value                       : " << x << '\n';
    std::cout << "address of x                  : " << &x << "\n\n";

    // Lvalue reference binds to an lvalue
    int& x_ref = x;
    x_ref = 20;
    std::cout << "x_ref value (after write)     : " << x_ref << '\n';
    std::cout << "address of x_ref              : " << &x_ref << " (same as x)\n\n";

    // const lvalue reference can bind to a temporary (rvalue) and extend its lifetime
    const int& const_ref = 5;    // temporary lives as long as const_ref
    std::cout << "const_ref (to rvalue 5)       : " << const_ref << '\n';
    std::cout << "address of const_ref          : " << &const_ref << "\n\n";

    // rvalue reference must bind to an rvalue
    int&& rref = 7;
    std::cout << "rref (rvalue reference)       : " << rref << '\n';
    std::cout << "address of rref               : " << &rref << "\n\n";

    // -----------------------------------------------------
    // std::vector basics + addresses
    // -----------------------------------------------------
    std::vector<int> vec {1, 2, 3, 4};
    std::cout << "[before move]\n";
    std::cout << "  address of vec (object)           : " << &vec << '\n';
    std::cout << "  vec.size()                        : " << vec.size() << '\n';
    std::cout << "  vec.data() (buffer start)         : " << static_cast<const void*>(vec.data()) << '\n';
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << "    vec[" << i << "] at " << static_cast<const void*>(&vec[i])
                  << " = " << vec[i] << '\n';
    }
    std::cout << '\n';

    // -----------------------------------------------------
    // Moving a vector transfers ownership of its buffer
    // -----------------------------------------------------
    std::cout << "Moving vec into new_vec...\n";
    std::vector<int> new_vec = std::move(vec);

    std::cout << "\n[after move]\n";
    std::cout << "  address of vec (moved-from)       : " << &vec << '\n';
    std::cout << "  vec.size()                        : " << vec.size()
              << "  (valid but unspecified state; size is often 0)\n";
    std::cout << "  vec.data()                        : " << static_cast<const void*>(vec.data()) << '\n';

    std::cout << "  address of new_vec                : " << &new_vec << '\n';
    std::cout << "  new_vec.size()                    : " << new_vec.size() << '\n';
    std::cout << "  new_vec.data()                    : " << static_cast<const void*>(new_vec.data()) << '\n';
    for (std::size_t i = 0; i < new_vec.size(); ++i)
    {
        std::cout << "    new_vec[" << i << "] at " << static_cast<const void*>(&new_vec[i])
                  << " = " << new_vec[i] << '\n';
    }
    std::cout << '\n';

    // It is OK to *query* a moved-from vector (e.g., size(), data()).
    // Do not use its old elements; assume its contents are unspecified.

    // -----------------------------------------------------
    // Passing the vector by reference (no copy; same addresses)
    // -----------------------------------------------------
    std::cout << "Passing new_vec to inspect_vector...\n\n";
    inspect_vector(new_vec);

    // -----------------------------------------------------
    // Fixed-size array (no heap allocation, contiguous layout)
    // -----------------------------------------------------
    std::cout << "Creating a 3x3 array and passing it by reference...\n";
    const double mat[3][3] =
    {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    std::cout << "address of mat (3x3 array)         : " << &mat << '\n';
    std::cout << "mat[0][0]                          : " << mat[0][0] << '\n';
    std::cout << "mat[2][2]                          : " << mat[2][2] << "\n\n";

    std::cout << "Passing mat to matrix_function...\n\n";
    matrix_function(mat);

    return 0;
}
