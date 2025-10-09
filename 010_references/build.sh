#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ References.cpp -o References.x
    ./References.x

} 2>&1 | tee build.log
