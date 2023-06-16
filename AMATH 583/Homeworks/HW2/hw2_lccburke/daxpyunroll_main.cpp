#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "refBLAS.hpp"

int main() {
    int ntrials = 3;
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

    std::cout << "daxpyunroll performance test:" << std::endl;

    for (int n : sizes) {
        std::vector<double> x(n, 1.0);
        std::vector<double> y(n, 2.0);
        double alpha = 3.0;

        auto start = std::chrono::high_resolution_clock::now();
        for (int t = 0; t < ntrials; t++) {
            daxpy_unroll(alpha, x, y);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        long double avg_time = static_cast<long double>(duration.count()) / ntrials;
        long double flops = 2 * n;
	long double mflops = (flops / (avg_time * 1e-6)) / 1e6;

        std::cout << "n: " << n << ", Average time: " << avg_time << " ns, FLOPs: " << mflops << " MFLOPs" << std::endl;
    }

    return 0;
}

