#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include <omp.h>
#include "../gpu-controller/GPUController.hpp"
#include "../gpu-controller/TestUtils.hpp"
using namespace std;

struct message {
    float *data;
    int size;
};

std::string path;
int method; // 0: "gpu" default
int activation; // 1: "yes" default
// Neurons
//  * N = number of input neurons
//  * H = number of hidden neurons
//  * M = number of output neurons
int N, M, H;
// Default values
// - The amount of iteration isn't used in this model.
int iter, th;

message msg;
int msg_num;
float *data;
float *output;

// Initialization function
bool init(int argc, char *argv[]);
