#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR

{
    mkdir -p build
    cd build

    cmake ..

    cmake --build . -- -j

    cd ../
    ctest --test-dir build -V


} 2>&1 | tee build/build.log

mkdir -p bin
cp build/src/HelloWorld.x bin/HelloWorld.x

./bin/HelloWorld.x
