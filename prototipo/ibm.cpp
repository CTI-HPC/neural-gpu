#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>

#include "ibm.hpp"


float get_next_value(std::stringstream& s) {
    std::string cell;
    std::getline(s, cell, ',');
    return atof(cell.c_str());
}

void read_indicator_file(std::vector<daily_indicators>& input, std::string file_name) {
    std::ifstream source(file_name.c_str());
    std::string line;

    while (std::getline(source, line)) {
        std::stringstream line_stream(line);
        daily_indicators x;

        x.open      = get_next_value(line_stream);
        x.high      = get_next_value(line_stream);
        x.low       = get_next_value(line_stream);
        x.close     = get_next_value(line_stream);
        x.volume    = get_next_value(line_stream);
        x.adj_close = get_next_value(line_stream);

        input.push_back(x);
    }
}


void read_weights_ih(float weights_ih[], int n_input, int n_hidden, std::string file_name) {
    std::ifstream source(file_name.c_str());
    std::string line;

    for (int h = 0; h < n_hidden; ++h) {
        std::getline(source, line);
        std::stringstream line_stream(line);
        for (int i = 0; i < n_input; ++i) {
            weights_ih[h * n_input + i] = get_next_value(line_stream);
        }
    }
}

void read_weights_ho(float weights_ho[], int n_hidden, int n_output, std::string file_name) {
    std::ifstream source(file_name.c_str());
    std::string line;

    /* test model file has only one line */
    std::getline(source, line);
    std::stringstream line_stream(line);

    for (int h = 0; h < n_hidden; ++h)
        weights_ho[h] = get_next_value(line_stream);
}


void print_matrix(float matrix[], int nr_rows, int nr_cols) {
    for (int i = 0; i < nr_rows; i++) {
        for (int j = 0; j < nr_cols; j++)
            std::cout << std::setprecision(3) <<
                         std::setw(8) <<
                         matrix[i * nr_rows + j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

