#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "refBLAS.hpp"

int main() {
    std::cout << "dgemv performance test:" << std::endl;

    int ntrial = 10;

    for (int n = 2; n <= 1024; n *= 2) {
        std::vector<std::vector<double>> A(n, std::vector<double>(n, 0));
        std::vector<double> x(n, 0);
        std::vector<double> y(n, 0);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-10, 10);

        for (int i = 0; i < n; i++) {
            x[i] = dis(gen);
            y[i] = dis(gen);
            for (int j = 0; j < n; j++) {
                A[i][j] = dis(gen);
            }
        }

        double alpha = 1.0;
        double beta = 1.0;

        auto start = std::chrono::steady_clock::now();
        for (int t = 0; t < ntrial; t++) {
            dgemv(alpha, A, x, beta, y);
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::micro> elapsed = (end - start) / ntrial;
        double avg_time = elapsed.count();

        long double flops = 2.0 * n * n;
        long double mflops = (flops / (avg_time * 1e-6)) / 1e6;

        std::cout << "n: " << n << ", Average time: " << avg_time << " microseconds, FLOPs: " << mflops << " MFLOPs" << std::endl;
    }

    return 0;
}

