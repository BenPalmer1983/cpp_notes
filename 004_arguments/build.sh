#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 Arguments.cpp -o Arguments.x
    ./Arguments.x arg1 arg2

} 2>&1 | tee build.log

