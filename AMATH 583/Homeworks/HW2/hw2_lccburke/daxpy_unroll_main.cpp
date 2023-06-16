#include <iostream>
#include <vector>
#include <chrono>
#include "refBLAS.hpp"

int main() {
    int ntrials = 3;
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int block_sizes[] = {1, 2, 4, 8, 16, 32, 64};

    std::cout << "daxpy_unroll performance test:" << std::endl;

    for (int n : sizes) {
        std::vector<double> x(n, 1.0);
        std::vector<double> y(n, 2.0);
        double a = 3.0;

        std::cout << "n: " << n << std::endl;

        for (int block_size : block_sizes) {
            auto start = std::chrono::high_resolution_clock::now();
            for (int t = 0; t < ntrials; t++) {
                std::vector<double> y_copy(y);  // Make a copy of y to ensure consistent initial state

                daxpy_unroll(a, x, y_copy, block_size);
            }
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double avg_time = static_cast<long double>(duration.count()) / ntrials;
            long double flops = 2 * n;
            long double mflops = (flops / (avg_time * 1e-6)) / 1e6;

            std::cout << "Block size: " << block_size << ", Average time: " << avg_time << " ns, FLOPs: " << mflops << " MFLOPs" << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}



