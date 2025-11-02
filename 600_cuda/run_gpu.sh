#!/bin/bash
source /opt/intel/oneapi/setvars.sh
export SYCL_DEVICE_FILTER=cuda

./cuda.x 10
./cuda.x 100
./cuda.x 1000
./cuda.x 10000
