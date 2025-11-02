#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ Regex.cpp -o Regex.x
    ./Regex.x

} 2>&1 | tee build.log



