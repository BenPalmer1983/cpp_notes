#!/bin/bash
set -Eeuo pipefail

trap 'echo "❌ Error on line $LINENO (exit code $?)" >&2' ERR

{
    mkdir -p build
    cd build

    cmake ..

    cmake --build . -- -j

    cd ../
    ctest --test-dir build -V

    echo "Copy"
    cp build/src/PortScanner.x PortScanner.x

    echo "Test Run"
    ./PortScanner.x

} 2>&1 | tee build/build.log
