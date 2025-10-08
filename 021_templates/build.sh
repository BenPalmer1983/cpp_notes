#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 main.cpp -o Templates.x
    ./Templates.x

} 2>&1 | tee build.log

