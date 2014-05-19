#pragma once
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <iterator>
#include "ibm.hpp"


float logistic(float x);

/**
 * @fn forward_pass
 *
 * @param n_input     Number of neurons in the input layer.
 * @param n_hidden    Number of neurons in the hidden layer.
 * @param n_output    Number of neurons in the output layer.
 * @param input       Array of input data.
 * @param hidden      Array where hidden layer data will be kept.
 * @param output      Array where output will be written.
 * @param weights_ih  Array of weights between input and hidden layers (row-order, size n_input * n_hidden).
 * @param weights_ho  Array of weights between hidden and output layers (row-order, size n_hidden * n_output).
 */

void forward_pass(int n_input, int n_hidden, int n_output,
                    float input[], float hidden[], float output[],
                    float weights_ih[], float weights_ho[]);

