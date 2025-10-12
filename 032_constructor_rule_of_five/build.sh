#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ ConstructorRuleOfFive.cpp -o ConstructorRuleOfFive.x
    ./ConstructorRuleOfFive.x

} 2>&1 | tee build.log



