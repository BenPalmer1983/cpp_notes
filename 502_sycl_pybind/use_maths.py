#!/usr/bin/env python3
import time
import numpy
import maths

# 1. Problem size
N = 3500          # rows = cols
K = 3500          # inner dimension

# 2. Random data (double precision)
rng = numpy.random.default_rng(seed=42)
A = rng.random((N, K), dtype=numpy.float64)
B = rng.random((K, N), dtype=numpy.float64)
C = rng.random((N, N), dtype=numpy.float64)

k = 2.0
l = 3.0

# 3. Warm‑up
_ = maths.Maths.dgemm_sycl(k, A, B, l, C, N, K)
_ = k * (A @ B) + l * C

# 4. Benchmark SYCL (GPU)
t0 = time.perf_counter()
X_sycl = maths.Maths.dgemm_sycl(k, A, B, l, C, N, K)
t_sycl = time.perf_counter() - t0

# 5. Benchmark NumPy (CPU)
t0 = time.perf_counter()
X_np = k * (A @ B) + l * C
t_np = time.perf_counter() - t0

# 6. Verify correctness
max_diff = numpy.max(numpy.abs(X_sycl - X_np))
print(f"max abs diff: {max_diff:.2e}")

# 7. Print timings
print(f"SYCL (GPU) time : {t_sycl:.3f} s")
print(f"NumPy (CPU) time: {t_np:.3f} s")
print(f"Speedup         : {t_np / t_sycl:.2f}x")