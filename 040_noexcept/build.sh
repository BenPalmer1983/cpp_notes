#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ Noexcept.cpp -o Noexcept.x
    ./Noexcept.x

} 2>&1 | tee build.log

echo ""
echo ""

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{

    g++ -DDEMO_TERMINATE Noexcept.cpp -o Noexcept.x
    ./Noexcept.x

} 2>&1 | tee build_error.log



