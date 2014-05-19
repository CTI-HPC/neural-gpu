#include "gpu-forward-pass.hpp"
#include "cublas.h"


__global__ void set_one(float *array, int i) {
    int id = threadIdx.x + blockIdx.x * blockDim.x;
    if (id == 0) {
        array[i] = 1.0f;
    }
}


__device__ float gpu_logistic(float x) {
    return 1 / (1 + expf(-x));
}


__global__ void activation_function(float x[], int n) {
    int id = threadIdx.x + blockIdx.x * blockDim.x;

    if (id < n){
        x[id] = gpu_logistic(x[id]);
    }
}


void initialize_gpu_arrays(int n_input,  float d_input[],
                           int n_hidden, float d_hidden[],
                           int n_output, float d_output[]) {
    set_one<<<1, 1>>>(d_input,  n_input);
    set_one<<<1, 1>>>(d_hidden, n_hidden);
}


/* Matrix-vector multiplication b = Ax
 * for a contiguous, row-major matrix A.
 * Matrix A has to have been set like this:
 *
 *   st = cublasSetMatrix(COLS, ROWS, _, a_host, COLS, a_device, COLS);
 */
void matrix_vector_product(int nr_rows, int nr_cols,
                           float *b, float *a, float *x) {
    cublasSgemv('t', nr_cols, nr_rows,
      1.0f, a, nr_cols,
            x, 1,
      0.0f, b, 1);
}


void gpu_forward_pass(int n_input, int n_hidden, int n_output,
                      float input[], float hidden[], float output[],
                      float d_input[], float d_hidden[], float d_output[],
                      float d_weights_ih[], float d_weights_ho[],
                      int activation)
{
    /* Assumption: d_input and d_hidden already have their ones at their tails.
     * (initialize_gpu_arrays must have already been called).  */

    int T, B;

    cublasSetVector(n_input, sizeof(float), input, 1, d_input, 1);

    matrix_vector_product(
      /* matrix size: */ n_hidden, n_input + 1,
      /* operands:    */ d_hidden, d_weights_ih, d_input);

    T = 128;
    B = int(std::ceil(n_hidden / float(T)));
    activation_function<<<B, T>>>(d_hidden, n_hidden);

    cudaThreadSynchronize();

    matrix_vector_product(
      /* matrix size: */ n_output, n_hidden + 1,
      /* operands:    */ d_output, d_weights_ho, d_hidden);

    if (activation) {
        T = 128;
        B = int(std::ceil(n_hidden / float(T)));
        activation_function<<<B, T>>>(d_output, n_output);
        cudaThreadSynchronize();
    }

    cublasGetVector(n_output, sizeof(float), d_output, 1, output, 1);

}

