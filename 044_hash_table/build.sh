#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -std=c++23 HashTable.cpp -o HashTable.x
    ./HashTable.x

} 2>&1 | tee build.log



