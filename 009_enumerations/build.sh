#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 Enumerations.cpp -o Enumerations.x
    ./Enumerations.x

} 2>&1 | tee build.log



