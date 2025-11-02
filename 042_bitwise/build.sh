#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ Bitwise.cpp -o Bitwise.x
    ./Bitwise.x

} 2>&1 | tee build.log



