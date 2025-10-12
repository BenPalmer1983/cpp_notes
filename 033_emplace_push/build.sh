#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ EmplacePush.cpp -o EmplacePush.x
    ./EmplacePush.x

} 2>&1 | tee build.log



