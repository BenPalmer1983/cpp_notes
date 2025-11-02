#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ OpenMP.cpp -o OpenMP.x
    ./OpenMP.x

} 2>&1 | tee build.log

