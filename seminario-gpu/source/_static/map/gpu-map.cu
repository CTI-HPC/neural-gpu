#include "gpu-map.hpp"
#include <cuda_runtime_api.h>
#include <math.h>
#include <stdio.h>

// El kernel d_f implementa la función f aplicadas a un valor x cualquiera.
// Este kernel está declarado con el calificador __device__,
// por lo que sólo puede ser llamado por código que está siendo ejecutado
// en la GPU.

__device__ float d_f(float x) {
    float s = 0.0;
    for (int k = 1; k <= 10000; ++k) {
        s += sinf(2 * float(M_PI) * k * x);
    }
    return s;
}

// El kernel map_f se encarga de que cada hebra
// ejecute la función d_f con el argumento apropiado.

__global__ void map_f(float x[]) {
    unsigned i = threadIdx.x + blockIdx.x * blockDim.x;
    x[i] = d_f(x[i]);
}

// gpu_map debe hacer toda la burocracia de ejecutar código en la GPU:
// reserva memoria, copia el arreglo, lanza el kernel,
// copia el resultado de vuelta y libera la memoria.

void gpu_map(float x[], unsigned n) {

    // Juegue.

}

