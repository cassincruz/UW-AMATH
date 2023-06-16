#include "refBLAS.hpp"

void dgemv(double alpha, const std::vector<std::vector<double>>& A, const std::vector<double>& x, double beta, std::vector<double>& y) {
    int m = A.size();
    int n = A[0].size();

    if (n != x.size()) {
        throw std::invalid_argument("The number of columns in A must match the size of vector x.");
    }

    if (y.size() != m) {
        throw std::invalid_argument("The size of vector y must match the number of rows in A.");
    }

    std::vector<double> Ax(m, 0.0);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            Ax[i] += A[i][j] * x[j];
        }
    }

    for (int i = 0; i < m; i++) {
        y[i] = alpha * Ax[i] + beta * y[i];
    }
}


