#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ AutoTypeDeduction.cpp -o AutoTypeDeduction.x
    ./AutoTypeDeduction.x

} 2>&1 | tee build.log



