#include "../gpu-controller/GPUController.hpp"
#include "../gpu-controller/TestUtils.hpp"
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <omp.h>


int main(int argc, char *argv[]) {

    std::string path;
    int method = 0; // "gpu" default
    int activation = 1; // "yes" default
    // Neurons
    //  * N = number of input neurons
    //  * H = number of hidden neurons
    //  * M = number of output neurons
    int N, M, H;
    // Default values
    int iter = 1, th = 128;

    if(!check_flags(argc,argv,path,method,activation, iter,th)){
        return 1;
    }

    parse_info_file(path,N,H,M);

    GPUController c(N, H, M);
    c.set_method(method);
    c.set_activation(activation);
    cout << "Loading parameters." << endl;
    c.load_parameters(path);

    vector<float> matrix;
    load_matrix(matrix,path+"input.txt");

    cout << "Pushing input vectors into the controller." << endl;
    cout<<"\n Elements..."<<matrix.size()<<endl;

    double ini_time = omp_get_wtime();
    for (int i = 0; i < iter; i++) {
        c.push(&matrix[0],matrix.size());
    }
    double end_time = omp_get_wtime();
    // Getting the timer precision used in omp_get_wtime()
    //   Number of seconds between processor clock ticks
    double tick = omp_get_wtick();
    cout << "Average kernel time omp: " << 1e6 * (end_time - ini_time) / iter << " [µs]" << endl;
    cout << "Timer precision: " << tick << endl;
    cout << "Ticks per second: " << 1.0/tick << endl;

    print_diff(path, c.get_output(), M);

    return 0;
}
