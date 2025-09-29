#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR

{
    mkdir -p build
    cd build

    cmake ..

    cmake --build . -- -j

    cd ../

} 2>&1 | tee build/build.log

mkdir -p bin
cp build/src/Pointers.x bin/Pointers.x

./bin/Pointers.x
