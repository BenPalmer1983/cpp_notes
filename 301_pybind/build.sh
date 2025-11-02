#!/bin/bash
set -Eeuo pipefail

trap 'echo "ERROR on line $LINENO (exit code $?)" >&2' ERR
{
    if [[ ! -d ".venv" ]]; then
        echo "Creating Python virtual environment (.venv) ..."
        python3 -m venv .venv
        source .venv/bin/activate
        python3 -m pip install -U pip setuptools wheel pybind11 numpy
    fi

    # Activate the virtual environment
    source .venv/bin/activate

    # Print to user
    echo "Virtual environment activated: $(which python3)"

    # Build
    python3 -m pip install -e .


    # Test run
    python3 use_maths.py

} 2>&1 | tee build.log



