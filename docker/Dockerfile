# syntax=docker/dockerfile:1
# Ubuntu 22.04 + CUDA (nvcc) + OpenCL + SYCL (oneAPI+Codeplay) + OpenMP + OpenMP offload (Clang 20.1.0)
FROM nvidia/cuda:12.4.1-devel-ubuntu22.04

ENV DEBIAN_FRONTEND=noninteractive

# Base toolchain + OpenCL loader/headers + utils
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build git pkg-config \
    curl wget ca-certificates gnupg lsb-release software-properties-common \
    python3 python3-pip \
    ocl-icd-libopencl1 ocl-icd-opencl-dev opencl-headers clinfo \
    xz-utils \
    && rm -rf /var/lib/apt/lists/*

# ---- SYCL: Intel oneAPI DPC++ compiler (icpx) ----
RUN wget -O- https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB \
      | gpg --dearmor | tee /usr/share/keyrings/oneapi-archive-keyring.gpg >/dev/null && \
    echo "deb [signed-by=/usr/share/keyrings/oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" \
      > /etc/apt/sources.list.d/oneAPI.list && \
    apt-get update && apt-get install -y --no-install-recommends \
      intel-oneapi-compiler-dpcpp-cpp \
    && rm -rf /var/lib/apt/lists/*

# ---- SYCL CUDA backend (Codeplay: SYCL -> NVIDIA CUDA) ----
RUN wget -qO - https://developer.codeplay.com/apt/public.key \
      | gpg --dearmor | tee /usr/share/keyrings/codeplay-keyring.gpg >/dev/null && \
    echo "deb [signed-by=/usr/share/keyrings/codeplay-keyring.gpg] https://developer.codeplay.com/apt all main" \
      > /etc/apt/sources.list.d/codeplay.list && \
    apt-get update && apt-get install -y --no-install-recommends \
      oneapi-nvidia-12.0 \
    && rm -rf /var/lib/apt/lists/*

# ---- LLVM/Clang 20.1.0 (generic Linux binary) ----
ARG LLVM_VER=20.1.0
ARG LLVM_TARBALL=LLVM-${LLVM_VER}-Linux-X64.tar.xz
ARG LLVM_URL=https://github.com/llvm/llvm-project/releases/download/llvmorg-${LLVM_VER}/${LLVM_TARBALL}
RUN set -eux; \
    mkdir -p /opt; \
    curl -fL "${LLVM_URL}" -o /tmp/${LLVM_TARBALL}; \
    mkdir -p /opt/llvm-${LLVM_VER}; \
    tar -xJf /tmp/${LLVM_TARBALL} -C /opt/llvm-${LLVM_VER} --strip-components=1; \
    rm -f /tmp/${LLVM_TARBALL}

# ---- Environment ----
# Add CUDA & LLVM to PATH/LIB; auto-load oneAPI env in interactive shells
ENV PATH="/opt/llvm-${LLVM_VER}/bin:/usr/local/cuda/bin:${PATH}"
ENV LD_LIBRARY_PATH="/opt/llvm-${LLVM_VER}/lib:${LD_LIBRARY_PATH}"
RUN printf '%s\n' '. /opt/intel/oneapi/setvars.sh > /dev/null || true' > /etc/profile.d/oneapi.sh

# (Optional) quick sanity during build — uncomment if desired
# RUN bash -lc "nvcc --version && clinfo -l || true && icpx -fsycl --version && clang++ --version"

CMD ["/bin/bash"]
