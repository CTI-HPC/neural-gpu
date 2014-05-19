#pragma once

#include <string>
#include <vector>

#define INPUT_SIZE  1000
#define HIDDEN_SIZE 5000
#define OUTPUT_SIZE  500

#define DATA_DIR "../modelo-prueba-grande/"
#define INPUT_FILE      (DATA_DIR "input.txt")
#define HIDDEN_FILE     (DATA_DIR "hidden.txt")
#define OUTPUT_FILE     (DATA_DIR "output.txt")
#define WEIGHTS_IH_FILE (DATA_DIR "weights_ih.txt")
#define WEIGHTS_HO_FILE (DATA_DIR "weights_ho.txt")

void load_matrix(std::vector<float>& input, std::string file_name);
void print_matrix(const std::vector<float>& matrix, int nr_rows, int nr_cols);

