#include <iostream>
#include <chrono>
#include <vector>
#include <cblas.h>

// Perform matrix multiplication using OpenBLAS
void openblas_matrix_multiply(int n, const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, double alpha, double beta) {
    // Use cblas_dgemm function for matrix multiplication
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, alpha, A.data(), n, B.data(), n, beta, C.data(), n);
}

int main() {
    const double alpha = 1.0, beta = 1.0;

    for (int n = 16; n <= 8192; n *= 2) {
        std::vector<double> A(n * n, 1.0); // Init matrices 
        std::vector<double> B(n * n, 2.0);
        std::vector<double> C(n * n, 3.0);

        const int n_trials = 3;
        double total_time = 0.0;

        // Perform multiplication n_trials times and measure average execution time
        for (int trial = 0; trial < n_trials; ++trial) {
            auto startTime = std::chrono::high_resolution_clock::now();
            openblas_matrix_multiply(n, A, B, C, alpha, beta);
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = endTime - startTime;

            total_time += diff.count();
        }

        double avg_time = total_time / n_trials;
        // Performance in GFLOPs = (2n^3) / (avg_time * 10^9)
        double gflops = (2.0 * n * n * n) / (avg_time * 1e9);

        std::cout << "Matrix Size: " << n << " Avg Time: " << avg_time << " GFLOPs: " << gflops << std::endl;
    }

    return 0;
}
