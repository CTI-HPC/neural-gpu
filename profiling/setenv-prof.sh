#!/bin/bash

# Este script configura el entorno
# para compilar kernels con profiling activado.

export CUDA_PROFILE=1
export CUDA_PROFILE_CONFIG=profiler-config.txt
export CUDA_PROFILE_LOG=profile.csv

