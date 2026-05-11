
// first cell
%%writefile matrix_input.txt
1 2 3
4 5 6
7 8 9

9 8 7
6 5 4
3 2 1


// second cell
#include <iostream>
#include <cuda_runtime.h>
using namespace std;

#define N 3

// CUDA Kernel
__global__ void multiply(int *A, int *B, int *C) {

    int row = threadIdx.y;
    int col = threadIdx.x;

    int sum = 0;

    for(int k = 0; k < N; k++) {
        sum += A[row * N + k] * B[k * N + col];
    }

    C[row * N + col] = sum;
}

int main() {

    int size = N * N * sizeof(int);

    int A[N][N], B[N][N], C[N][N];

    // Input Matrix A
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    // Input Matrix B
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> B[i][j];
        }
    }

    int *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    dim3 threads(N, N);

    multiply<<<1, threads>>>(d_A, d_B, d_C);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    cout << "Matrix Multiplication Result:\n";

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}


// !nvcc matrix_mul.cu -o matrix_mul
// !./matrix_mul < matrix_input.txt