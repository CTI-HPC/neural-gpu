#pragma once

#include <string>
#include <vector>
#define EXAMPLE_FILE  "../ejemplos/IBM.csv"

struct daily_indicators {
    float open;
    float high;
    float low;
    float close;
    float volume;
    float adj_close;
};

void read_indicator_file(std::vector<daily_indicators>& input, std::string file_name);

void read_weights_ih(float weights_ih[], int n_input, int n_hidden, std::string file_name);
void read_weights_ho(float weights_ho[], int n_hidden, int n_output, std::string file_name);

void print_matrix(float matrix[], int nr_rows, int nr_cols);

