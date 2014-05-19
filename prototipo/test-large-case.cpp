#include "red-serial.hpp"
#include "large-case.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <omp.h>
#define N_TIME 1

typedef std::vector<float> vf;

int main() {
    vf input, hidden;
    vf computed_output, actual_output;
    vf weights_ih, weights_ho;
    float t_ini,t_end;

    std::cout << "Loading vector." << std::endl;
    load_matrix(input, INPUT_FILE);

    std::cout << "Loading weight_ih." << std::endl;
    load_matrix(weights_ih, WEIGHTS_IH_FILE);

    std::cout << "Loading weight_ho." << std::endl;
    load_matrix(weights_ho, WEIGHTS_HO_FILE);

    std::cout << "Loading actual output." << std::endl;
    load_matrix(actual_output, OUTPUT_FILE);

    assert(input.size() == INPUT_SIZE);
    assert(weights_ih.size() == INPUT_SIZE * HIDDEN_SIZE);
    assert(weights_ho.size() == HIDDEN_SIZE * OUTPUT_SIZE);
    assert(actual_output.size() == OUTPUT_SIZE);

    hidden.resize(HIDDEN_SIZE);
    computed_output.resize(OUTPUT_SIZE);

    std::cout << "Forward pass." << std::endl;
    t_ini = omp_get_wtime();
    for(int i = 0; i < N_TIME; i++){
    forward_pass(INPUT_SIZE, HIDDEN_SIZE, OUTPUT_SIZE,
            &input[0], &hidden[0], &computed_output[0],
            &weights_ih[0], &weights_ho[0]);
    }
    t_end = omp_get_wtime();

    std::cout << "First values of computed output: " << std::endl;
    print_matrix(computed_output, 1, 8);

    std::cout << "Actual first values: " << std::endl;
    print_matrix(actual_output, 1, 8);

    std::cout << "Forward Pass Time: " << std::endl;
    std::cout << (t_end - t_ini)/(float)N_TIME << std::endl;

}

