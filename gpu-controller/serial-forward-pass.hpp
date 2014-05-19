#pragma once

/**
 * @fn serial_forward_pass
 *
 * @param n_input     Number of neurons in the input layer.
 * @param n_hidden    Number of neurons in the hidden layer.
 * @param n_output    Number of neurons in the output layer.
 * @param input       Array of input data (must be of size n_input + 1).
 * @param hidden      Array where hidden layer data will be kept (must be of size n_hidden + 1).
 * @param output      Array where output will be written (must be of size n_output).
 * @param weights_ih  Array of weights between input and hidden layers (row-order, size (n_input + 1) * n_hidden).
 * @param weights_ho  Array of weights between hidden and output layers (row-order, size (n_hidden + 1) * n_output).
 */

void serial_forward_pass(int n_input, int n_hidden, int n_output,
                         float input[], float hidden[], float output[],
                         float weights_ih[], float weights_ho[],
                         int activation);

