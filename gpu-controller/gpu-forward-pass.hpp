#pragma once

/**
 * @fn gpu_forward_pass
 *
 * @param n_input     Number of neurons in the input layer.
 * @param n_hidden    Number of neurons in the hidden layer.
 * @param n_output    Number of neurons in the output layer.
 * @param input       Array of input data.
 * @param hidden      Array where hidden neurons' values will be kept.
 * @param output      Array where output will be written.
 * @param weights_ih  Array of weights between input and hidden layers (row-order, size n_input * n_hidden).
 * @param weights_ho  Array of weights between hidden and output layers (row-order, size n_hidden * n_output).
 */

void gpu_forward_pass(int n_input, int n_hidden, int n_output,
                         float input[], float hidden[], float output[],
                         float *d_input, float *d_hidden, float *d_output,
                         float weights_ih[], float weights_ho[],
                         int activation);

void initialize_gpu_arrays(int n_input,  float d_input[],
                           int n_hidden, float d_hidden[],
                           int n_output, float d_output[]);
