# build
docker build -t gpu-stack:jammy .
docker run --rm -it --gpus all gpu-stack:jammy bash
