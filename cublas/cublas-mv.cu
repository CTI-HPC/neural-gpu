#include <stdlib.h>
#include <stdio.h>
#include "cublas.h"
#define HA 3
#define WA 3
#define S 3

void printMat(float*P,int uWP,int uHP){
    int i,j,z=0;

    for(i=0;i<uHP;i++){
        printf("\n");
        for(j=0;j<uWP;j++){
            printf("%f ",P[z]);
            z++;
        }
    }
}
void printVect(float*P,int sP){
    int j;

    for(j=0;j<sP;j++)
        printf("%f ",P[j]);

    printf("\n");
}

int  main (int argc, char** argv) {
    // Estructura para comprobar el estado de cualquier llamada cublas
    //cublasStatus status;
    int i,j,z=0;
    cublasInit();

    float *A = (float*)malloc(HA*WA*sizeof(float));
    float *B = (float*)malloc(S*sizeof(float));
    float *C = (float*)malloc(S*sizeof(float));

    // llenado matriz A
    for (i=0;i<HA;i++){
        for (j=0;j<WA;j++){
            A[z] = (float) i+j+1;
            z++;
        }
    }

    // llenado vector B
    z = 0;
    for (i=0;i<S;i++){
       B[z] = i+1;
       C[z] = 0;
        z++;
    }

    float* AA;
    float* BB;
    float* CC;

    // Asignación de memoria
    cublasAlloc(HA*WA,sizeof(float),(void**)&AA);
    cublasAlloc(S,sizeof(float),(void**)&BB);
    cublasAlloc(S,sizeof(float),(void**)&CC);

    // Copiado de memoria Host to Device
    cublasSetMatrix(HA,WA,sizeof(float),A,HA,AA,HA);
    cublasSetVector(S,sizeof(float),B,1,BB,1);

    // Llamada a kernel de cublas para multiplicar matrix por vector
    cublasSgemv('t',HA,WA,1,AA,WA,BB,1,0,CC,1);
    cudaThreadSynchronize();

    // Copiado de memoria Device to Host
    cublasGetVector(S,sizeof(float),CC,1,C,1);

    // Verificacion contenido
    printf("\nMatriz A:\n");
    printMat(A,WA,HA);
    printf("\nVector B:\n");
    printVect(B,S);
    printf("\nVector C:\n");
    printVect(C,S);

    free(A);
    free(B);
    free(C);
    cublasFree(AA);
    cublasFree(BB);
    cublasFree(CC);

    cublasShutdown();
    return EXIT_SUCCESS;
  }
