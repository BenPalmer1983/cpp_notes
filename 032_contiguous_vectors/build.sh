#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ ContiguousVectors.cpp -o ContiguousVectors.x
    ./ContiguousVectors.x

} 2>&1 | tee build.log



