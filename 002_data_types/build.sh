#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 DataTypes.cpp -o DataTypes.x
    ./DataTypes.x

} 2>&1 | tee build.log

