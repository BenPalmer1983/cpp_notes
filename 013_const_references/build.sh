#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 ConstReferences.cpp -o ConstReferences.x
    ./ConstReferences.x --verbose

} 2>&1 | tee build.log



