// Run this in a Colab cell:
%%writefile input.txt
1 2 3 4 5
5 4 3 2 1



// second cell
#include <iostream>
#include <cuda_runtime.h>
using namespace std;

// CUDA Kernel
__global__ void vectorAdd(int *A, int *B, int *C, int n) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if(i < n) {
        C[i] = A[i] + B[i];
    }
}

int main() {

    int n = 5;
    int size = n * sizeof(int);

    int A[n], B[n], C[n];

    // Take input
    for(int i = 0; i < n; i++)
        cin >> A[i];

    for(int i = 0; i < n; i++)
        cin >> B[i];

    int *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    vectorAdd<<<1, n>>>(d_A, d_B, d_C, n);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    cout << "Vector Addition Result:\n";

    for(int i = 0; i < n; i++)
        cout << C[i] << " ";

    cout << endl;

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}



// !nvcc vector_add.cu -o vector_add
// !./vector_add < input.txt