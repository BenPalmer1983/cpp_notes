#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 FunctionsIntroduction.cpp -o FunctionsIntroduction.x
    ./FunctionsIntroduction.x

} 2>&1 | tee build.log
