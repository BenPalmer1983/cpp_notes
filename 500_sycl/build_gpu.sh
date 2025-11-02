#!/bin/bash
source /opt/intel/oneapi/setvars.sh
export SYCL_DEVICE_FILTER=cuda
icpx -std=c++17 \
     -O2 \
     -qopenmp \
     -fsycl \
     -fsycl-targets=nvptx64-nvidia-cuda,spir64_x86_64 \
     sycl.cpp -o sycl.x

