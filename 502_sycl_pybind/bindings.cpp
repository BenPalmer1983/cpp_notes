#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "dgemm.hpp"


static std::vector<double> to_flat(const pybind11::array_t<double>& a) {
    pybind11::buffer_info i = a.request();
    if (i.ndim != 2) throw std::runtime_error("2-D array required");
    const double* src = static_cast<const double*>(i.ptr);
    size_t rows = i.shape[0], cols = i.shape[1];
    size_t rs = i.strides[0]/sizeof(double), cs = i.strides[1]/sizeof(double);
    std::vector<double> f(rows*cols);
    for (size_t r=0; r<rows; ++r)
        for (size_t c=0; c<cols; ++c)
            f[r*cols + c] = src[r*rs + c*cs];
    return f;
}

static pybind11::array_t<double> to_numpy(const std::vector<double>& v, size_t r, size_t c) {
    pybind11::array_t<double> out({r,c});
    std::memcpy(out.mutable_data(), v.data(), v.size()*sizeof(double));
    return out;
}

PYBIND11_MODULE(maths, m) {
    m.doc() = "SYCL DGEMM";

    auto ns = m.def_submodule("Maths", "C++ namespace Maths");

    ns.def("dgemm_sycl",
        [](double k,
           const pybind11::array_t<double>& A,
           const pybind11::array_t<double>& B,
           double l,
           const pybind11::array_t<double>& C,
           size_t rows, size_t cols) {
            auto check = [&](const auto& a, size_t er, size_t ec, const char* n) {
                pybind11::buffer_info i = a.request();
                if (i.ndim!=2 || i.shape[0]!=er || i.shape[1]!=ec)
                    throw std::runtime_error(std::string(n)+" wrong shape");
            };
            check(A,rows,cols,"A");
            check(B,cols,rows,"B");
            check(C,rows,rows,"C");

            auto Af = to_flat(A), Bf = to_flat(B), Cf = to_flat(C);
            auto Xf = Maths::Dgemm::dgemm_sycl(k, Af, Bf, l, Cf, rows, cols);
            return to_numpy(Xf, rows, rows);
        },
        pybind11::arg("k"), pybind11::arg("A"), pybind11::arg("B"), pybind11::arg("l"), pybind11::arg("C"),
        pybind11::arg("rows"), pybind11::arg("cols"));
}