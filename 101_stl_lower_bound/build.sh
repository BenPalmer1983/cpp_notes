#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ stl_lower_bound.cpp -o stl_lower_bound.x
    ./stl_lower_bound.x

} 2>&1 | tee build.log



