#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <mkl.h>

float blas_logistic(float x) {
    return 1 / (1 + expf(-x));
}

void mkl_forward_pass(int n_input, int n_hidden, int n_output,
                      float input[], float hidden[], float output[],
                      float weights_ih[], float weights_ho[],
                      bool activation)
{
    int h, j;
    const float hidden_bias = 1.0;
    const float output_bias = 1.0;


    /* Initialize neurons. */
    std::fill_n(hidden, n_hidden, 0.0);
    std::fill_n(output, n_output, 0.0);

    cblas_sgemv(CblasRowMajor, CblasNoTrans, n_input, n_hidden,
                1.0, weights_ih, n_input,
                     input,  1,
                0.0, hidden, 1);

    /* Hidden neuron activation */
    for (h = 0; h < n_hidden; ++h)
        hidden[h] = blas_logistic(hidden[h] + hidden_bias);

    cblas_sgemv(CblasRowMajor, CblasNoTrans, n_hidden, n_output,
                1.0, weights_ho, n_hidden,
                     hidden,  1,
                0.0, output, 1);


    /* Output neuron activation */
    if (activation) {
        for (j = 0; j < n_output; ++j)
            output[j] = blas_logistic(output[j] + output_bias);
    }

}


