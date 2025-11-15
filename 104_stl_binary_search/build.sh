#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ stl_binary_search.cpp -o stl_binary_search.x
    ./stl_binary_search.x

} 2>&1 | tee build.log



