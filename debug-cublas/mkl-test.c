#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mkl.h"

#if 0
void report_error(cublasStatus_t st, char *msg) {
    char error_name[50];
#   define RED(s) ("\033[;1;31m" s "\033[0m")
#   define SET(s) (strcpy(error_name, RED(s)))
    if      (st == CUBLAS_STATUS_NOT_INITIALIZED)  SET("CUBLAS_STATUS_NOT_INITIALIZED");
    else if (st == CUBLAS_STATUS_ALLOC_FAILED)     SET("CUBLAS_STATUS_ALLOC_FAILED");
    else if (st == CUBLAS_STATUS_INVALID_VALUE)    SET("CUBLAS_STATUS_INVALID_VALUE");
    else if (st == CUBLAS_STATUS_MAPPING_ERROR)    SET("CUBLAS_STATUS_MAPPING_ERROR");
    else if (st == CUBLAS_STATUS_EXECUTION_FAILED) SET("CUBLAS_STATUS_EXECUTION_FAILED");
    else if (st == CUBLAS_STATUS_INTERNAL_ERROR)   SET("CUBLAS_STATUS_INTERNAL_ERROR");
    else return;
#   undef RED
#   undef SET
    printf("%s: %s\n", error_name, msg);
}
#endif

void print_vector(float vector[], int size) {
    int i;
    for (i = 0; i < size; ++i)
        printf("%12g", vector[i]);
    printf("\n");
}


int main() {

#   define ROWS 3
#   define COLS 5

    float a[] = {
        6, 2, 1, 4, 5,
        3, 9, 3, 8, 2,
        1, 3, 2, 2, 1
    };
    float x[] = { 5, 4, 3, 2, 1 };
    float b[] = { 54, 78, 28 };

    float bh[ROWS];

#   define LDA COLS
#   define INC 1
#   define F   (sizeof(float))

#   if 0
    cublasSgemv('t', COLS, ROWS,
            1, ad, LDA,
               xd, INC,
            0, bd, INC);
#   endif


    cblas_sgemv(CblasRowMajor, CblasNoTrans, ROWS, COLS,
                1.0, a, LDA,
                     x, INC,
                0.0, bh, INC);

    printf("Computed b:\t"); print_vector(bh, ROWS);
    printf("Expected b:\t"); print_vector(b , ROWS);

    return 0;
}

