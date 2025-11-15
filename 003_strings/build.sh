#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 Strings.cpp -o Strings.x
    ./Strings.x

} 2>&1 | tee build.log



