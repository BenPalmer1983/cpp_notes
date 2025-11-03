#!/usr/bin/env bash
# Build maths*.so directly with icpx (no CMake)
# Usage: ./build_basic.sh [cuda|cpu]    default: cuda

set -e

source /opt/intel/oneapi/setvars.sh
export SYCL_DEVICE_FILTER=cuda

# --- oneAPI env (avoid nounset issues) ---
set +u
export OCL_ICD_FILENAMES="${OCL_ICD_FILENAMES-}"

set -u

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


# --- pick backend ---
TARGET="${1:-cuda}"
case "$TARGET" in
  cuda) SYCL_TGT="nvptx64-nvidia-cuda"; export SYCL_DEVICE_FILTER=cuda ;;
  cpu)  SYCL_TGT="spir64_x86_64";       export SYCL_DEVICE_FILTER=cpu  ;;
  *) echo "Use: cuda | cpu"; exit 2 ;;
esac
echo "SYCL target: $SYCL_TGT (SYCL_DEVICE_FILTER=$SYCL_DEVICE_FILTER)"

# --- choose python (use your venv if you have one) ---
PY="${PYTHON:-python3}"

# ensure headers are present for THIS python
$PY -m pip install -U pip >/dev/null
$PY -m pip install -U pybind11 numpy >/dev/null

# collect include & link flags from THIS python
INCFLAGS="$($PY -m pybind11 --includes 2>/dev/null || true)"
if [ -z "$INCFLAGS" ]; then
  # fallback if the entrypoint is missing
  INCFLAGS="$($PY - <<'PY'
import sysconfig, pybind11, numpy as np
parts = []
for k in ("INCLUDEPY",):
    v = sysconfig.get_config_var(k)
    if v: parts.append("-I"+v)
parts.append("-I"+pybind11.get_include())
parts.append("-I"+np.get_include())
print(" ".join(parts))
PY
)"
fi

EXT="$($PY - <<'PY'
import sysconfig; print(sysconfig.get_config_var("EXT_SUFFIX"))
PY
)"

LDFLAGS="$($PY - <<'PY'
import sysconfig
print(sysconfig.get_config_var("LDFLAGS") or "")
PY
)"

echo "Using includes: $INCFLAGS"

# --- compile: bindings.cpp -> maths*.so ---
icpx -O3 -fPIC -shared -std=c++17 \
     -fsycl -fsycl-device-code-split=per_kernel -fsycl-targets="${SYCL_TGT}" \
     ${INCFLAGS} \
     bindings.cpp \
     -o "maths${EXT}" \
     ${LDFLAGS}

echo "Built: maths${EXT}"
