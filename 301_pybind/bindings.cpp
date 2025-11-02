

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <vector>
#include "LinAlg.hpp"


// Include PyBind and all the Classes needed for this library


// Convert to C++ vector
static std::vector<double> to_vector(pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast> arr)
{
    pybind11::buffer_info buf = arr.request();
    const double* ptr = static_cast<const double*>(buf.ptr);
    return std::vector<double>(ptr, ptr + buf.size);
}

// Module name: maths
// Top level object: m
PYBIND11_MODULE(maths, m)
{

    // 
    m.doc() = "maths module";


    // Create a Python submodule named "Maths" to mirror the C++ namespace.
    pybind11::module_ maths_namespace = m.def_submodule("Maths", "Namespace Maths");


    // Bind the LinAlg class into the Maths submodule (static method only).
    pybind11::class_<Maths::LinAlg>(maths_namespace, "LinAlg")
    .def_static(
        "axpy",
        [](pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast> A,
        pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast> x,
        pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast> y)
        {
            // Check dimensions of input arrays
            if (A.ndim() != 2) 
            {
                throw std::invalid_argument("A must be 2D");
            }
            if (x.ndim() != 1) 
            {
                throw std::invalid_argument("x must be 1D");
            }
            if (y.ndim() != 1) 
            {
                throw std::invalid_argument("y must be 1D");
            }

            // Get and save the sizes
            std::size_t rows = static_cast<std::size_t>(A.shape(0));
            std::size_t cols = static_cast<std::size_t>(A.shape(1));

            // Check sizes are correct for the calculation before attempting to run
            if (static_cast<std::size_t>(x.shape(0)) != cols) 
            {
                throw std::invalid_argument("len(x) must equal A.shape[1]");
            }
            if (static_cast<std::size_t>(y.shape(0)) != rows) 
            {
                throw std::invalid_argument("len(y) must equal A.shape[0]");
            }

            // Convert to C++ vectors
            std::vector<double> A_flat = to_vector(A);
            std::vector<double> x_v = to_vector(x);
            std::vector<double> y_v = to_vector(y);

            // Do the calculation
            std::vector<double> out = Maths::LinAlg::axpy(A_flat, rows, cols, x_v, y_v);

            // Create 1D numpy array for the result
            pybind11::array_t<double> result({static_cast<pybind11::ssize_t>(rows)});
            auto r = result.mutable_unchecked<1>();
            for (pybind11::ssize_t i = 0; i < static_cast<pybind11::ssize_t>(rows); ++i) 
            {
                r(i) = out[static_cast<std::size_t>(i)];
            }
            return result;
        },
        "Compute result = A @ x + y where A is (rows, cols), x is (cols,), y is (rows,)."
    );
}

