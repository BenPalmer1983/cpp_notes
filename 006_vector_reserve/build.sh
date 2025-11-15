#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 VectorReserve.cpp -o VectorReserve.x
    ./VectorReserve.x

} 2>&1 | tee build.log

