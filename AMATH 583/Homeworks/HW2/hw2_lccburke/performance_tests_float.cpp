#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "refBLAS.hpp"

template <typename T>
double measure_axpy_performance(const T alpha, const std::vector<T>& x, std::vector<T>& y, int ntrial) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ntrial; ++i) {
        axpy(alpha, x, y);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / static_cast<double>(ntrial);
}

template <typename T>
double measure_gemv_performance(T alpha, const std::vector<std::vector<T>>& A, const std::vector<T>& x, T beta, std::vector<T>& y, int ntrial) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ntrial; ++i) {
        gemv(alpha, A, x, beta, y);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / static_cast<double>(ntrial);
}

template <typename T>
double measure_gemm_performance(T alpha, const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B, T beta, std::vector<std::vector<T>>& C, int ntrial) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ntrial; ++i) {
        gemm(alpha, A, B, beta, C);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / static_cast<double>(ntrial);
}

int main() {
    int ntrial = 3;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    std::cout << "axpy performance test (float):" << std::endl;
    for (int n = 2; n <= 1024; n *= 2) {
        float alpha = distribution(generator);
        std::vector<float> x(n, distribution(generator));
        std::vector<float> y(n, distribution(generator));
        double avg_time = measure_axpy_performance(alpha, x, y, ntrial);
        double flops = (2.0 * n - 1) / avg_time * 1e6;
        std::cout << "n: " << n << ", Average time: " << avg_time << " microseconds, FLOPs: " << flops << " MFLOPs" << std::endl;
    }

    std::cout << "\ngemv performance test (float):" << std::endl;
    for (int n = 2; n <= 1024; n *= 2) {
        float alpha = distribution(generator);
        float beta = distribution(generator);
        std::vector<std::vector<float>> A(n, std::vector<float>(n, distribution(generator)));
        std::vector<float> x(n, distribution(generator));
        std::vector<float> y(n, distribution(generator));
        double avg_time = measure_gemv_performance(alpha, A, x, beta, y, ntrial);
        double flops = (2.0 * n * n - n) / avg_time * 1e6;
        std::cout << "n: " << n << ", Average time: " << avg_time << " microseconds, FLOPs: " << flops << " MFLOPs" << std::endl;
    }

    std::cout << "\ngemm performance test (float):" << std::endl;
    for (int n = 2; n <= 1024; n *= 2) {
        float alpha = distribution(generator);
        float beta = distribution(generator);
        std::vector<std::vector<float>> A(n, std::vector<float>(n, distribution(generator)));
        std::vector<std::vector<float>> B(n, std::vector<float>(n, distribution(generator)));
        std::vector<std::vector<float>> C(n, std::vector<float>(n, distribution(generator)));
        double avg_time = measure_gemm_performance(alpha, A, B, beta, C, ntrial);
        double flops = (2.0 * n * n * n) / avg_time * 1e6;
        std::cout << "n: " << n << ", Average time: " << avg_time << " microseconds, FLOPs: " << flops << " MFLOPs" << std::endl;
    }

    return 0;
}

