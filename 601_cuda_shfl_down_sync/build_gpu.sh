#!/bin/bash
source /opt/intel/oneapi/setvars.sh
export SYCL_DEVICE_FILTER=cuda

nvcc -std=c++17 \
    -O3 \
     -arch=sm_86 \
    -Xcompiler "-fno-fast-math -fno-unsafe-math-optimizations -ffp-contract=off" \
       shfl_down_sync.cu \
    -o shfl_down_sync.x



