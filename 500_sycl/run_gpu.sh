#!/bin/bash
source /opt/intel/oneapi/setvars.sh
export SYCL_DEVICE_FILTER=cuda

./sycl.x 10
./sycl.x 100
./sycl.x 1000
./sycl.x 10000
