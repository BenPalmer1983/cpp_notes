#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ stl_sort.cpp -o stl_sort.x
    ./stl_sort.x

} 2>&1 | tee build.log



