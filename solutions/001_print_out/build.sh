#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ PrintOut.cpp -o PrintOut.x
    ./PrintOut.x

} 2>&1 | tee build.log



