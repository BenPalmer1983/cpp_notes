#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ Variant.cpp -o Variant.x
    ./Variant.x

} 2>&1 | tee build.log

