#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <iterator>
#include "ibm.hpp"
#include "red-serial.hpp"


int main() {

    using namespace std;

    vector<daily_indicators> data;
    read_indicator_file(data, "../modelo-prueba/input.txt");

#   define N 6
#   define H 10
#   define M 1

    float input [N];
    float hidden[H];
    float output[M];
    float weights_ih[N * H];
    float weights_ho[H * M];

    read_weights_ih(weights_ih, N, H, "../modelo-prueba/weights_ih.txt");
    read_weights_ho(weights_ho, H, M, "../modelo-prueba/weights_ho.txt");

    /* Use values from the first row of the test file
     * as input to the neural network. */
    memcpy(input, &data[0], N * sizeof(float));

    forward_pass(N, H, M, input, hidden, output, weights_ih, weights_ho);

    cout << "Input:  ";
    copy(input,  input  + N, ostream_iterator<float>(cout, " "));
    cout << endl;

    cout << "Hidden: ";
    copy(hidden, hidden + H, ostream_iterator<float>(cout, " "));
    cout << endl;

    cout << "Output: ";
    copy(output, output + M, ostream_iterator<float>(cout, " "));
    cout << endl;
}
