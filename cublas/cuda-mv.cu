#include <stdlib.h>
#include <stdio.h>
#include "cublas.h"
#include <iostream>
#define HA 4
#define WA 3
#define S 3
using namespace std;

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

__global__ void smv(float A[], float B[], float C[], int height,int s)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    float sum = 0;
    __shared__ extern float vec_s[];
    if(threadIdx.x < s)
        vec_s[threadIdx.x] = B[threadIdx.x];
    __syncthreads();

    if(tid < height){
      #pragma unroll 8
      for(int i=0; i < s; i++){
          sum += A[tid*s+i] * vec_s[i];
      }
      C[tid] = sum;
    }
}


int  main (int argc, char** argv) {
    int i,j,z=0;
    int TpB = 32;
    int BpG = 32;

    float *A = (float*)malloc(HA*WA*sizeof(float));
    float *B = (float*)malloc(S*sizeof(float));
    float *C = (float*)malloc(HA*sizeof(float));

    // llenado matriz A
    for (i=0;i<HA;i++){
        for (j=0;j<WA;j++){
            A[z] = (float) i+j+1;
            z++;
        }
    }
    cout << z << endl;
    // llenado vector B
    z = 0;
    for (i=0;i<S;i++){
       B[z] = i+1;
       C[z] = 0;
        z++;
    }

    z = 0;
    for (i=0;i<HA;i++){
       C[z] = 0;
        z++;
    }

    float* AA;
    float* BB;
    float* CC;

    cudaMalloc((void**)&AA,HA*WA*sizeof(float));
    cudaMalloc((void**)&BB,S*sizeof(float));
    cudaMalloc((void**)&CC,HA*sizeof(float));

    cudaMemcpy(AA , A , HA*WA*sizeof(float) , cudaMemcpyHostToDevice);
    cudaMemcpy(BB , B , S*sizeof(float)     , cudaMemcpyHostToDevice);

    smv <<< BpG, TpB, S >>> (AA,BB,CC,HA,S);
    cudaThreadSynchronize();

    cudaMemcpy(C,CC,HA*sizeof(float),cudaMemcpyDeviceToHost);

    // Verificacion contenido
    printf("\nMatriz A:\n");
    printMat(A,WA,HA);
    printf("\nVector B:\n");
    printVect(B,S);
    printf("\nVector C:\n");
    printVect(C,HA);

    free(A);
    free(B);
    free(C);
    cudaFree(AA);
    cudaFree(BB);
    cudaFree(CC);
  }
