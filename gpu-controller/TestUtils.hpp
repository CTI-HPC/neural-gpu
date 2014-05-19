#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>
#include <cmath>
namespace po = boost::program_options;
using namespace std;

/**
 * @fn parse_info_file
 *
 * @param path File path to the information file
 * @param N    Number of neurons in the input layer
 * @param H    Number of neurons in the hidden layer
 * @param M    Number of neurons in the output layer
 */
void parse_info_file(string path, int &N, int &H, int &M);

/**
 * @fn check_flags
 *
 * @param argc         Number of command line arguments
 * @param argv         Command line arguments
 * @param path         Directory Path to the data models
 * @param method       Execution method. The default value is 0, which means GPU mode, and the CPU mode is 1.
 * @param activation   Activation function on the output vector. 0 means no, and 1 yes.
 * @param iter         Number of iterations to peform the time measurement.
 * @param th           Number of threads for the GPU mode. The number of threads depends of the GPU device.
 */
bool check_flags(int argc, char *argv[], string &path, int &method, int &activation,int &iter, int &th);

/**
 * @fn print_diff
 *
 * @param path    File path to the information file
 * @param output  Array where output will be written.
 * @param M       Number of neurons in the output layer
 */
void print_diff(string path, float *output, int M);


/*
 * @fn load_matrix
 *
 * @param matrix     Vector associated to the IH and HO matrix.
 * @param file_name  Filename of the matrix sources.
 */

void load_matrix(std::vector<float>& matrix, std::string file_name);

