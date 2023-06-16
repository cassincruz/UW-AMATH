#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "refBLAS.hpp"
#include "perf_tests.hpp"

// Helper function to generate random data
void generate_random_data(int m, int n, std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>& y) {
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

// Function to measure the execution time of a function
template <typename Func, typename... Args>
double measure_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();

    func(std::forward<Args>(args)...);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    return static_cast<double>(duration) / 1000.0; // Convert microseconds to milliseconds
}

void daxpy_test() {
    int ntrials = 3;
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

    std::cout << "daxpy performance test:" << std::endl;

    for (int n : sizes) {
        std::vector<double> x(n, 1.0);
        std::vector<double> y(n, 2.0);
        double a = 3.0;

        auto start = std::chrono::high_resolution_clock::now();
        for (int t = 0; t < ntrials; t++) {
            daxpy(a, x, y);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        long double avg_time = static_cast<long double>(duration.count()) / ntrials;
        long double flops = 2 * n;
	    long double mflops = (flops / (avg_time * 1e-6)) / 1e6;

        std::cout << "n: " << n << ", Average time: " << avg_time << " ns, FLOPs: " << mflops << " MFLOPs" << std::endl;
    }
}



// ... (keep the other functions like daxpy_performance_test here)

