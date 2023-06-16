#include "refBLAS.hpp"

void daxpy(double alpha, const std::vector<double>& x, std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("The sizes of the input vectors x and y do not match.");
    }

    size_t n = x.size();
    for (size_t i = 0; i < n; i++) {
        y[i] = alpha * x[i] + y[i];
    }
}


