#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "refBLAS.hpp"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10, 10);

    int ntrials = 3;

    std::cout << "dgemm performance test:" << std::endl;
    for (int n = 2; n <= 1024; n *= 2) {
        std::vector<std::vector<double>> A(n, std::vector<double>(n));
        std::vector<std::vector<double>> B(n, std::vector<double>(n));
        std::vector<std::vector<double>> C(n, std::vector<double>(n));

        // Initialize matrices A and B with random values
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i][j] = dis(gen);
                B[i][j] = dis(gen);
            }
        }

        // Randomly choose alpha and beta
        double alpha = dis(gen);
        double beta = dis(gen);

        double avg_time = 0;

        for (int trial = 0; trial < ntrials; ++trial) {
            auto start = std::chrono::high_resolution_clock::now();
            dgemm(alpha, A, B, beta, C);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::micro> elapsed = end - start;
            avg_time += elapsed.count();
        }

        avg_time /= ntrials;

        long double flops = 2.0 * n * n * n;
        long double mflops = (flops / (avg_time * 1e-6)) / 1e6;

        std::cout << "n: " << n << ", Average time: " << avg_time << " microseconds, FLOPs: " << mflops << " MFLOPs" << std::endl;
    }

    return 0;
}

