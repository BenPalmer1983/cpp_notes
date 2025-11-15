#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 HelloWorld.cpp -o HelloWorld.x
    ./HelloWorld.x

} 2>&1 | tee build.log



