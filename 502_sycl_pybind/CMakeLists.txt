cmake_minimum_required(VERSION 3.22)
project(maths LANGUAGES CXX)

# -------------------------------------------------
# FORCE icpx (Intel oneAPI SYCL compiler)
# -------------------------------------------------
set(CMAKE_CXX_COMPILER icpx CACHE STRING "SYCL compiler")

find_package(pybind11 REQUIRED)

pybind11_add_module(maths MODULE bindings.cpp)

# SYCL flags (now understood by icpx)
target_compile_options(maths PRIVATE
    -fsycl
    -fsycl-targets=nvptx64-nvidia-cuda,spir64_x86_64
    -O3
)
target_link_options(maths PRIVATE
    -fsycl
    -fsycl-targets=nvptx64-nvidia-cuda,spir64_x86_64
)

target_compile_features(maths PRIVATE cxx_std_17)