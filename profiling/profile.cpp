#include "../gpu-controller/GPUController.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <omp.h>
#include <sys/time.h>

#define N_TIMES 1000
#define N 1000
#define H 5000
#define M 500

int main() {
    using namespace std;

    GPUController c(N, H, M);
    cout << "Loading parameters." << endl;
    c.load_parameters("example-nn");

    vector<float> matrix;
    load_matrix(matrix,"example-nn/input.txt");

    cout << "Pushing input vectors into the controller." << endl;
    cout<<"\n Elements..."<<matrix.size()<<endl;

    float ini_time = omp_get_wtime();
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);   // Instante inicial

    for (int i = 0; i < N_TIMES; i++) {
        c.push(&matrix[0],matrix.size());
    }

    gettimeofday(&tf, NULL);   // Instante final
    tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
    printf("Average kerne time sys/time: %g microsegundos\n", tiempo/1000.0);
    float end_time = omp_get_wtime();
    cout << ini_time << endl;
    cout << end_time << endl;
    cout << "Average kernel time omp: " << 1e6 * (end_time - ini_time) / N_TIMES << " [µs]" << endl;
    return 0;
}
