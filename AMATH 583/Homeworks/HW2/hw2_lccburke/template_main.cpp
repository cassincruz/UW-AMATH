#include <iostream>
#include <chrono>
#include <random>
#include "refBLAS.hpp"

// Helper function to generate random data
void generate_random_data(int m, int n, std::vector<std::vector<float>>& A, std::vector<float>& x, std::vector<float>& y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = dis(gen);
        }
    }

    for (int i = 0; i < n; ++i) {
        x[i] = dis(gen);
    }

    for (int i = 0; i < m; ++i) {
        y[i] = dis(gen);
    }
}

int main() {
    for (int n = 2; n <= 1024; n *= 2) {
        int m = n;

        // Generate random data
        std::vector<std::vector<float>> A(m, std::vector<float>(n));
        std::vector<float> x(n);
        std::vector<float> y(m);
        generate_random_data(m, n, A, x, y);

        // Call axpy, gemv, and gemm functions
        int axpy_iterations = 1000;
        auto start_time_axpy = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < axpy_iterations; ++i) {
            axpy<float>(1.0f, x, y);
        }
        auto end_time_axpy = std::chrono::high_resolution_clock::now();

        auto start_time_gemv = std::chrono::high_resolution_clock::now();
        gemv<float>(1.0f, A, x, 0.0f, y);
        auto end_time_gemv = std::chrono::high_resolution_clock::now();

        auto start_time_gemm = std::chrono::high_resolution_clock::now();
        gemm<float>(1.0f, A, A, 0.0f, A);
        auto end_time_gemm = std::chrono::high_resolution_clock::now();

        // Measure execution time
        auto duration_axpy = std::chrono::duration_cast<std::chrono::microseconds>(end_time_axpy - start_time_axpy).count() / static_cast<double>(axpy_iterations);
        auto duration_gemv = std::chrono::duration_cast<std::chrono::microseconds>(end_time_gemv - start_time_gemv).count();
        auto duration_gemm = std::chrono::duration_cast<std::chrono::microseconds>(end_time_gemm - start_time_gemm).count();

        // Output the results
        std::cout << "n = " << n << std::endl;

        double duration_axpy_sec = static_cast<double>(duration_axpy) / 1000000.0;
        double flops_axpy = 2 * n / duration_axpy_sec;
        std::cout << "  axpy execution time: " << duration_axpy_sec * 1000.0 << " ms, FLOPS: " << flops_axpy << std::endl;

        double duration_gemv_sec = static_cast<double>(duration_gemv) / 1000000.0;
        double flops_gemv = 2 * m * n / duration_gemv_sec;
        std::cout << "  gemv execution time: " << duration_gemv_sec * 1000.0 << " ms, FLOPS: " << flops_gemv << std::endl;

        double duration_gemm_sec = static_cast<double>(duration_gemm) / 1000000.0;
        double flops_gemm = 2 * m * n * n / duration_gemm_sec;
        std::cout << "  gemm execution time: " << duration_gemm_sec * 1000.0 << " ms, FLOPS: " << flops_gemm << std::endl;
    }

    return 0;
}


