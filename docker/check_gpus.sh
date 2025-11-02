#!/bin/bash

# Docker should list NVIDIA as a runtime or show GPU capability
docker info | grep -Ei 'Runtime|nvidia'

# Minimal test (should print the same nvidia-smi table you posted)
docker run --rm --gpus all nvidia/cuda:12.2.2-base-ubuntu20.04 nvidia-smi

