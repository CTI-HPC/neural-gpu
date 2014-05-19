#include "GPUController.hpp"
#include "TestUtils.hpp"
#include "serial-forward-pass.hpp"
#include "gpu-forward-pass.hpp"
#include "mkl-forward-pass.hpp"
#include "cublas.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>



void GPUController::serial_forward_pass() {
    ::serial_forward_pass(
            n_input, n_hidden, n_output,
            &input[0], &hidden[0], &output[0],
            &weights_ih[0], &weights_ho[0],
            this->probabilistic);
}


void GPUController::mkl_forward_pass() {
    ::mkl_forward_pass(
            n_input, n_hidden, n_output,
            &input[0], &hidden[0], &output[0],
            &weights_ih[0], &weights_ho[0],
            this->probabilistic);
}


void GPUController::gpu_forward_pass() {
    ::gpu_forward_pass(
            n_input, n_hidden, n_output,
            &input[0], &hidden[0], &output[0],
            d_input, d_hidden, d_output,
            d_weights_ih, d_weights_ho,
            this->probabilistic);
}


GPUController::GPUController(int n_input, int n_hidden, int n_output) {
    this->n_input  = n_input;
    this->n_hidden = n_hidden;
    this->n_output = n_output;

    hidden.resize(n_hidden + 1);
    output.resize(n_output);

    cublasInit();

    /* d_input and d_hidden must have an additional element
     * for storing the 1 needed for taking bias into account.
     * This 1 is set once by calling initialize_gpu_arrays(...)
     * from the load_parameters method.  */
    cublasAlloc(n_input + 1,  sizeof(float), (void **) &d_input);
    cublasAlloc(n_hidden + 1, sizeof(float), (void **) &d_hidden);
    cublasAlloc(n_output,     sizeof(float), (void **) &d_output);

    /* Weight matrices have an extra column
     * for storing the biases.  */
    cublasAlloc(n_hidden * (n_input + 1),  sizeof(float), (void **) &d_weights_ih);
    cublasAlloc(n_output * (n_hidden + 1), sizeof(float), (void **) &d_weights_ho);

}

GPUController::~GPUController() {

    cublasFree(d_input);
    cublasFree(d_hidden);
    cublasFree(d_output);
    cublasFree(d_weights_ih);
    cublasFree(d_weights_ho);
    cublasShutdown();
}

void GPUController::load_parameters(std::string path) {
    std::string wih_file("weights_ih.txt");
    std::string who_file("weights_ho.txt");
    load_matrix(this->weights_ih, path + "/" + wih_file);
    load_matrix(this->weights_ho, path + "/" + who_file);

    if (weights_ih.size() != unsigned((n_input + 1) * n_hidden)) {
        std::cerr << "WARNING: weights_ih has " << weights_ih.size() << " elements, "
                  << "they should be " << (n_input + 1) * n_hidden << std::endl;
    }
    if (weights_ho.size() != unsigned((n_hidden + 1) * n_output)) {
        std::cerr << "WARNING: weights_ho has " << weights_ih.size() << " elements, "
                  << "they should be " << (n_hidden + 1) * n_output << std::endl;
    }

    cublasSetMatrix((n_input + 1), n_hidden, sizeof(float), &weights_ih[0],
            (n_input + 1), d_weights_ih, (n_input + 1));
    cublasSetMatrix((n_hidden + 1), n_output, sizeof(float), &weights_ho[0],
            (n_hidden + 1), d_weights_ho, (n_hidden + 1));

    initialize_gpu_arrays(n_input, d_input, n_hidden, d_hidden, n_output, d_output);

}

void GPUController::push(float *input_vector, int input_size) {
    input.clear();
    std::copy(input_vector,
              input_vector + input_size,
              std::back_inserter(this->input));
    if (cpu_mode){
        mkl_forward_pass();
    }
    else {
        gpu_forward_pass();
    }
}

void GPUController::set_method(int method){
    this->cpu_mode = method;
}

void GPUController::set_activation(int activation){
    this->probabilistic = activation;
}
