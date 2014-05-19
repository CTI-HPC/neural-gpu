#include "large-case.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>

void load_matrix(std::vector<float>& matrix, std::string file_name) {
    matrix.clear();
    std::ifstream source(file_name.c_str());
    std::back_insert_iterator<std::vector<float> > b(matrix);
    std::copy(std::istream_iterator<float>(source),
              std::istream_iterator<float>(),
              b);
}


void print_matrix(const std::vector<float>& matrix, int nr_rows, int nr_cols) {
    for (int i = 0; i < nr_rows; i++) {
        for (int j = 0; j < nr_cols; j++)
            std::cout << std::setprecision(2) <<
                         std::setw(10) <<
                         matrix.at(i * nr_rows + j);
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


