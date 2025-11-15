#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 StaticCast.cpp -o StaticCast.x
    ./StaticCast.x

} 2>&1 | tee build.log



