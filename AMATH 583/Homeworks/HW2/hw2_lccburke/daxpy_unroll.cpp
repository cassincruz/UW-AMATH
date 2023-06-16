#include "refBLAS.hpp"

void daxpy_unroll(double alpha, const std::vector<double>& x, std::vector<double>& y, int block_size) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("The sizes of the input vectors x and y do not match.");
    }

    if (block_size <= 0) {
        throw std::invalid_argument("The block size must be greater than 0.");
    }

    int n = x.size();
    int unroll_depth = 4;

    for (int i = 0; i <= n - unroll_depth; i += block_size) {
        for (int j = 0; j < block_size && i + j + unroll_depth - 1 < n; j++) {
            int idx = i + j;
            y[idx] = alpha * x[idx] + y[idx];
            y[idx + 1] = alpha * x[idx + 1] + y[idx + 1];
            y[idx + 2] = alpha * x[idx + 2] + y[idx + 2];
            y[idx + 3] = alpha * x[idx + 3] + y[idx + 3];
        }
    }

    // Process remaining elements
    for (int i = n - n % unroll_depth; i < n; i++) {
        y[i] = alpha * x[i] + y[i];
    }
}


