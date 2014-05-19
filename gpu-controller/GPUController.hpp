#pragma once
#include <vector>
#include <string>

/** Main class which is in charge of all the neural network processing and implementation. */

class GPUController {
private:
    /**
      * @defgroup HostVectors Host vectors
    */
    /*@{*/
    std::vector<float> input;
    std::vector<float> output;
    std::vector<float> hidden;
    std::vector<float> weights_ih;
    std::vector<float> weights_ho;
    /*@}*/

    /**
      * @defgroup DeviceVectors Device vectors
    */
    /*@{*/ 
    float* d_input;
    float* d_output;
    float* d_hidden;
    float* d_weights_ih;
    float* d_weights_ho;
    /*@}*/

    int n_input;
    int n_hidden;
    int n_output;
    int cpu_mode;
    int probabilistic;

    void serial_forward_pass();
    void mkl_forward_pass();
    void gpu_forward_pass();

public:
    /**
     * @fn GPUController
     *
     * @param n_input     Number of neurons in the input layer.
     * @param n_hidden    Number of neurons in the hidden layer.
     * @param n_output    Number of neurons in the output layer.
     */
    GPUController(int n_input, int n_hidden, int n_output);

    /**
     * @fn ~GPUController
     */
    ~GPUController();

    /**
     * @fn load_parameters
     *
     * @param Path to the directory where the model files
     *        (the weight matrices) are located.
     */
    void load_parameters(std::string path);

    /**
     * @fn push
     *
     * @param input_vector  Array of input data.
     * @param input_size    Size of the array.
     */
    void push(float *input_vector, int input_size);

    /**
     * @fn set_method
     *
     * @param method Option to execute the controller on the GPU (0) or CPU (1).
     */
    void set_method(int method);

    /**
     * @fn set_activation
     *
     * @param activation Option to apply an activation function on the output vector. 1 is yes, 0 is no.
     */
    void set_activation(int activation);

    /**
     * @fn get_output
     */
    float *get_output() { return &output[0]; };
};

