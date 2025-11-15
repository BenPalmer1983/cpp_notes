#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 Vector.cpp -o Vector.x
    ./Vector.x

} 2>&1 | tee build.log

