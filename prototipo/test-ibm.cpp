#include <iostream>
#include <vector>
#include <string>
#include "ibm.hpp"

using namespace std;

int main() {
    vector<daily_indicators> input;
    string file_name(EXAMPLE_FILE);
    read_indicator_file(input, EXAMPLE_FILE);

    daily_indicators x;

    /* Parse the file and print the first three rows.
     * Compare to the output of:
     *
     *     head IBM.csv -n3
     */
    for (int i = 0; i < 3; ++i) {
        x = input[i];
        cout << "Row " << i << endl;
        cout << "Open:     " << x.open << endl;
        cout << "High:     " << x.high << endl;
        cout << "Low:      " << x.low << endl;
        cout << "Close:    " << x.close << endl;
        cout << "Volume:   " << x.volume << endl;
        cout << "AdjClose: " << x.adj_close << endl;
        cout << endl;
    }

#   define N 6
#   define H 10
#   define M 1

    float weights_ih[N * H];
    float weights_ho[H * M];

    read_weights_ih(weights_ih, N, H, "../modelo-prueba/weights_ih.txt");
    read_weights_ho(weights_ho, H, M, "../modelo-prueba/weights_ho.txt");

    cout << "input-hidden weight matrix:" << endl;
    print_matrix(weights_ih, N, H);

    cout << "hidden-output weight matrix:" << endl;
    print_matrix(weights_ho, H, M);

}

