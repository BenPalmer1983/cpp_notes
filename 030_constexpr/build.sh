#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ ConstExpr.cpp -o ConstExpr.x
    ./ConstExpr.x

} 2>&1 | tee build.log



