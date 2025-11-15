#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ Pair.cpp -o Pair.x
    ./Pair.x

} 2>&1 | tee build.log



