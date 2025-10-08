#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ main.cpp -o Loops.x
    ./Loops.x

} 2>&1 | tee build.log

