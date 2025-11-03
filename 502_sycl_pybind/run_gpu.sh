#!/bin/bash
source /opt/intel/oneapi/setvars.sh
source .venv/bin/activate
export SYCL_DEVICE_FILTER=cuda

python3 use_maths.py
