#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ StaticCast.cpp -o StaticCast.x
    ./StaticCast.x

} 2>&1 | tee build.log



