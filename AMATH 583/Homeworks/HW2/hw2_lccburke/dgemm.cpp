#include "refBLAS.hpp"

void dgemm(const double alpha, const std::vector<std::vector<double>> &A,
           const std::vector<std::vector<double>> &B, const double beta,
           std::vector<std::vector<double>> &C) {
    int m = A.size();
    int n = B[0].size();
    int k = A[0].size();

    if (k != B.size()) {
        throw std::invalid_argument("The number of columns in A must match the number of rows in B.");
    }

    if (C.size() != m || C[0].size() != n) {
        throw std::invalid_argument("The dimensions of C do not match the result of the matrix multiplication.");
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int p = 0; p < k; p++) {
                sum += A[i][p] * B[p][j];
            }
            C[i][j] = alpha * sum + beta * C[i][j];
        }
    }
}


