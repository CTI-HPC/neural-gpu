#include "red-serial.hpp"
#include "large-case.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include "cublas.h"
#include <omp.h>
#define N_TIME 1

typedef std::vector<float> vf;

void mult_mv(float *matrix,int matrix_rows,int matrix_cols,float *vector, int vector_size,float *result,int result_size){
        cublasInit();
        float *d_matrix;
        float *d_vector;
        float *d_result;

        // Asignación de memoria
        cublasAlloc(matrix_rows*matrix_cols,sizeof(float),(void**)&d_matrix);
        cublasAlloc(vector_size,sizeof(float),(void**)&d_vector);
        cublasAlloc(result_size,sizeof(float),(void**)&d_result);

        // Copiado de memoria Host to Device
        cublasSetMatrix(matrix_rows,matrix_cols,sizeof(float),matrix,matrix_rows,d_matrix,matrix_rows);
        cublasSetVector(vector_size,sizeof(float),vector,1,d_vector,1);

        // Llamada a kernel de cublas para multiplicar d_matrix por vector
        cublasSgemv('t',matrix_cols,matrix_rows,1,d_matrix,matrix_cols,d_vector,1,0,d_result,1);
        cudaThreadSynchronize();

        cublasGetVector(result_size,sizeof(float),d_result,1,result,1);

        cublasFree(d_matrix);
        cublasFree(d_vector);
        cublasFree(d_result);

        cublasShutdown();
}

void parallel_forward_pass(int n_input, int n_hidden, int n_output,
                    float input[], float hidden[], float output[],
                    float weights_ih[], float weights_ho[]){

    int h, j;
    const float hidden_bias = 1.0;
    const float output_bias = 1.0;

    /* Initialize hidden-layer neurons with zero. */
    std::fill_n(hidden, n_hidden, 0.0);

    // Procesamiento de capa escondida con CUDA-CUBLAS
    mult_mv(weights_ih,n_hidden,n_input,input,n_input,hidden,n_hidden);

    /* Hidden neuron activation */
    for (h = 0; h < n_hidden; ++h)
        hidden[h] = logistic(hidden[h] + hidden_bias);

    mult_mv(weights_ho,n_output,n_hidden,hidden,n_hidden,output,n_output);

    /* Output neuron activation */
    for (j = 0; j < n_output; ++j)
        output[j] = logistic(output[j] + output_bias);

}

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
    parallel_forward_pass(INPUT_SIZE, HIDDEN_SIZE, OUTPUT_SIZE,
            &input[0], &hidden[0], &computed_output[0],
            &weights_ih[0], &weights_ho[0]);
    }
    t_end = omp_get_wtime();


    std::cout << "First values of computed output: " << std::endl;
    print_matrix(computed_output, 1, 16);

    std::cout << "Actual first values: " << std::endl;
    print_matrix(actual_output, 1, 16);

    std::cout << "Forward Pass Time: " << std::endl;
    std::cout << (t_end - t_ini)/(float)N_TIME << std::endl;

}

