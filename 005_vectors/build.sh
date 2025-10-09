#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ Vectors.cpp -o Vectors.x
    ./Vectors.x

} 2>&1 | tee build.log

