#include <iostream>
#include <chrono>
#include <vector>
#include <cublas_v2.h>

// Perform matrix multiplication using cuBLAS
void cublas_matrix_multiply(int n, const double* A, const double* B, double* C, double alpha, double beta) {
    cublasHandle_t handle;
    cublasCreate(&handle);

    // Use cublasDgemm function for matrix multiplication
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, n, n, n, &alpha, A, n, B, n, &beta, C, n);

    cublasDestroy(handle);
}

int main() {
    const double alpha = 1.0, beta = 0.0;
    const int n_start = 16, n_end = 8192, n_step = 2;

    double *d_A, *d_B, *d_C;

    for (int n = n_start; n <= n_end; n *= n_step) {
        std::vector<double> A(n * n, 1.0);
        std::vector<double> B(n * n, 1.0);
        std::vector<double> C(n * n, 0.0);

        // Allocate device memory
        cudaMalloc((void**)&d_A, n * n * sizeof(double));
        cudaMalloc((void**)&d_B, n * n * sizeof(double));
        cudaMalloc((void**)&d_C, n * n * sizeof(double));

        // Copy vectors from host to device
        cudaMemcpy(d_A, A.data(), n * n * sizeof(double), cudaMemcpyHostToDevice);
        cudaMemcpy(d_B, B.data(), n * n * sizeof(double), cudaMemcpyHostToDevice);
        cudaMemcpy(d_C, C.data(), n * n * sizeof(double), cudaMemcpyHostToDevice);

        const int n_trials = 3;
        double total_time = 0.0;

        // Perform multiplication n_trials times and measure average execution time
        for (int trial = 0; trial < n_trials; ++trial) {
            auto start_time = std::chrono::high_resolution_clock::now();
            cublas_matrix_multiply(n, d_A, d_B, d_C, alpha, beta);
            cudaDeviceSynchronize(); // Ensure computation is done
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end_time - start_time;

            total_time += diff.count();
        }

        // Copy array back to host
        cudaMemcpy(C.data(), d_C, n * n * sizeof(double), cudaMemcpyDeviceToHost);

        double avg_time = total_time / n_trials;
        // Performance in GFLOPs = (2n^3) / (avg_time * 10^9)
        double gflops = (2.0 * n * n * n) / (avg_time * 1e9);

        std::cout << "Matrix Size: " << n << " Avg Time: " << avg_time << " GFLOPs: " << gflops << std::endl;

        // Cleanup
        cudaFree(d_A);
        cudaFree(d_B);
        cudaFree(d_C);
    }

    return 0;
}
