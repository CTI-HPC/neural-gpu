#include "red-serial.hpp"
#include <algorithm>


float logistic(float x) {
    return 1 / (1 + expf(-x));
}


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
                    float weights_ih[], float weights_ho[])
{
    int h, i, j;
    const float hidden_bias = 1.0;
    const float output_bias = 1.0;

    /* Initialize hidden-layer neurons with zero. */
    std::fill_n(hidden, n_hidden, 0.0);

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
}

