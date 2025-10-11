#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ FunctionsWithVectors.cpp -o FunctionsWithVectors.x
    ./FunctionsWithVectors.x --verbose

} 2>&1 | tee build.log



