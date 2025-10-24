#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ stl_upper_bound.cpp -o stl_upper_bound.x
    ./stl_upper_bound.x

} 2>&1 | tee build.log



