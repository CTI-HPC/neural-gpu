#include "serial-forward-pass.hpp"
#include <cmath>
#include <algorithm>

float logistic(float x) {
    return 1 / (1 + expf(-x));
}


void serial_forward_pass(int n_input, int n_hidden, int n_output,
                         float input[], float hidden[], float output[],
                         float weights_ih[], float weights_ho[],
                         int activation)
{
    int h, i, j;

    /* Initialize neurons. */
    std::fill_n(hidden, n_hidden, 0.0);
    std::fill_n(output, n_output, 0.0);

    /* Take bias into account. */
    input[n_input] = 1.0f;
    hidden[n_hidden] = 1.0f;

    for (h = 0; h < n_hidden; ++h)
        for (i = 0; i < (n_input + 1); ++i)
            hidden[h] += weights_ih[h * (n_input + 1) + i] * input[i];

    /* Hidden neuron activation */
    for (h = 0; h < n_hidden; ++h)
        hidden[h] = logistic(hidden[h]);

    for (j = 0; j < n_output; ++j)
        for (h = 0; h < (n_hidden + 1); ++h)
            output[j] += weights_ho[j * (n_hidden + 1) + h] * hidden[h];

    if(activation){
        /* Output neuron activation */
        for (j = 0; j < n_output; ++j)
            output[j] = logistic(output[j]);
    }
}
