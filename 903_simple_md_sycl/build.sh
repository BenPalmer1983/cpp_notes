#!/bin/bash
source /opt/intel/oneapi/setvars.sh
export SYCL_DEVICE_FILTER=cuda
set -Eeuo pipefail

trap 'echo "❌ Error on line $LINENO (exit code $?)" >&2' ERR

{
    # Configure
    cmake -S . -B build -DCMAKE_CXX_COMPILER=icpx -DCMAKE_BUILD_TYPE=Release

    # Build
    cmake --build build -- -j

    # Run tests
    ctest --test-dir build -V

    echo "Copy"
    cp build/src/SimpleMD.x SimpleMD.x

    echo "Test Run"
    ./SimpleMD.x input.json

} 2>&1 | tee build.log