#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <iterator>
#include "ibm.hpp"

/* fully-static version */
#define N 6
#define H 10
#define M 1

/* Threads per block */
#define T 32

__device__ float logistic(float x){
        return 1 / (1 + expf(-x));
}


__device__ float forward_pass
            (int n_input, int n_hidden, int n_output,
            float input[], float hidden[], float output[],
            float weights_ih[], float weights_ho[])
{
    int h, i, j;

    const float hidden_bias = 1.0;
    const float output_bias = 1.0;

    /* Initialize hidden-layer neurons with zero. */
    // std::fill_n(hidden, n_hidden, 0.0);
    for (int i = 0; i <  n_hidden; i++){
        hidden[i] = 0.0;
        output[i] = 0.0;
    }

    for (h = 0; h < n_hidden; ++h)
        for (i = 0; i < n_input; ++i)
            hidden[h] += weights_ih[h * n_input + i] * input[i];

    /* Hidden neuron activation */
    for (h = 0; h < n_hidden; ++h)
        hidden[h] = logistic(hidden[h] + hidden_bias);

    for (j = 0; j < n_output; ++j)
        for (h = 0; h < n_hidden; ++h)
            output[j] += weights_ho[j * n_hidden + h] * hidden[h];

    /* Output neuron activation */
    for (j = 0; j < n_output; ++j)
        output[j] = logistic(output[j] + output_bias);

    return output[0];
}

__global__ void cuda_forward_pass
            (int n_input, int n_hidden, int n_output,
            float *inputs, float *hiddens, float *outputs,
            float weights_ih[], float weights_ho[], float *tmp_hidden)
{
    int t = threadIdx.x;
    int b = blockIdx.x;

    __shared__ float sh_input[N * T];
    __shared__ float sh_hidden[H * T];
    __shared__ float sh_weights_ih[N * H];
    __shared__ float sh_weights_ho[H * M];

    float *start;
    int nr_iterations;

    /* fetch the input data, chunk by chunk */
    start = inputs + N * T * b;
    for (int i = 0; i < N; ++i)
        sh_input[t + i * T] = start[t + i * T];

    __syncthreads();

    /* fetch weights_ih, chunk by chunk */
    nr_iterations = (int) ceilf((N * H) / (float) T);
    for (int i = 0; i < nr_iterations; ++i) {
        int index = t + i * T;
        if (index < N * H)
            sh_weights_ih[index] = weights_ih[index];
    }

    __syncthreads();

    /* fetch weights_ho, chunk by chunk */
    nr_iterations = (int) ceilf(H * M / (float) T);
    for (int i = 0; i < nr_iterations; ++i) {
        int index = t + i * T;
        if (index < H * M)
            sh_weights_ho[index] = weights_ho[index];
    }

    __syncthreads();

    /* for the time being, the output is 1-dimensional */
    float *my_hidden = sh_hidden + t * H;
    float *my_input  = sh_input  + t * N;
    float *my_output = &outputs[t + b * T];
    __syncthreads();
    outputs[t + b * T] = forward_pass(n_input, n_hidden, n_output,
            my_input, my_hidden, my_output,
            sh_weights_ih, sh_weights_ho);
}



int main(){
    using namespace std;

    vector<daily_indicators> data;
    read_indicator_file(data, "../modelo-prueba/input.txt");

    vector<float> outputs, hiddens;
    vector<daily_indicators> inputs;
    inputs.reserve(data.size());
    outputs.reserve(data.size());
    hiddens.reserve(H*data.size());

    // CUDA Threads per Block
    static int TpB = 32;
    // CUDA blocks per Grid
    static int BpG = 32;

    float weights_ih[N * H];
    float weights_ho[H * M];

    read_weights_ih(weights_ih, N, H, "../modelo-prueba/weights_ih.txt");
    read_weights_ho(weights_ho, H, M, "../modelo-prueba/weights_ho.txt");

    float *d_inputs;
    float *d_outputs;
    float *d_weights_ih;
    float *d_weights_ho;
    float *d_hiddens;

    int n_data = data.size();

    cudaMalloc((void**) &d_inputs,     n_data * N * sizeof(float));
    cudaMalloc((void**) &d_outputs,    n_data * M * sizeof(float));
    cudaMalloc((void**) &d_hiddens,    n_data * H * sizeof(float));

    cudaMalloc((void**) &d_weights_ih, N * H * sizeof(float));
    cudaMalloc((void**) &d_weights_ho, H * M * sizeof(float));


    cudaMemcpy(d_inputs,     &data[0],   n_data * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_weights_ih, weights_ih, N * H * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_weights_ho, weights_ho, H * M * sizeof(float), cudaMemcpyHostToDevice);

    cuda_forward_pass<<< BpG, TpB >>> (N, H, M,
                                         d_inputs, NULL, d_outputs,
                                         d_weights_ih, d_weights_ho, d_hiddens);

    cudaThreadSynchronize();

    cudaMemcpy(&inputs[0],  d_inputs,  n_data * N * sizeof(float),     cudaMemcpyDeviceToHost);
    cudaMemcpy(&outputs[0], d_outputs, n_data * M * sizeof(float),     cudaMemcpyDeviceToHost);
    cudaMemcpy(&weights_ih[0], d_weights_ih, N * H  * sizeof(float),     cudaMemcpyDeviceToHost);
    cudaMemcpy(&weights_ho[0], d_weights_ho, H * M  * sizeof(float),     cudaMemcpyDeviceToHost);
    cudaMemcpy(&hiddens[0], d_hiddens,  H*T* sizeof(float),     cudaMemcpyDeviceToHost);



    cudaFree(d_inputs);
    cudaFree(d_outputs);
    cudaFree(d_hiddens);
    cudaFree(d_weights_ih);
    cudaFree(d_weights_ho);


    cout << "Output: " << endl;
    //copy(outputs.begin(), outputs.end(), ostream_iterator<float>(cout, "\n"));
    for (int i = 0; i < H; i++)
        cout << outputs[i] << endl;
    cout << endl;

    return 0;
}
