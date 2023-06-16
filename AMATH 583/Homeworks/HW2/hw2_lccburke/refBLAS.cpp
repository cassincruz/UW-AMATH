#include "refBLAS.hpp"

template <typename T>
void axpy(T alpha, const std::vector<T>& x, std::vector<T>& y) {
    for (size_t i = 0; i < x.size(); ++i) {
        y[i] += alpha * x[i];
    }
}

template <typename T>
void gemv(T a, const std::vector<std::vector<T>>& A, const std::vector<T>& x, T b, std::vector<T>& y) {
    size_t m = A.size();
    size_t n = A[0].size();

    if (n != x.size()) {
        throw std::invalid_argument("The number of columns in A must match the size of vector x.");
    }

    if (y.size() != m) {
        throw std::invalid_argument("The size of vector y must match the number of rows in A.");
    }

    std::vector<T> Ax(m, 0);
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            Ax[i] += A[i][j] * x[j];
        }
    }

    for (size_t i = 0; i < y.size(); ++i) {
        y[i] = a * Ax[i] + b * y[i];
    }
}

template <typename T>
void gemm(T a, const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B, T b, std::vector<std::vector<T>>& C) {
    size_t A_rows = A.size();
    size_t A_cols = A[0].size();
    size_t B_cols = B[0].size();

    if (A_cols != B.size()) {
        throw std::invalid_argument("The number of columns in A must match the number of rows in B.");
    }

    std::vector<std::vector<T>> AB(A_rows, std::vector<T>(B_cols, 0));

    for (size_t i = 0; i < A_rows; ++i) {
        for (size_t j = 0; j < B_cols; ++j) {
            for (size_t k = 0; k < A_cols; ++k) {
                AB[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (size_t i = 0; i < A_rows; ++i) {
        for (size_t j = 0; j < B_cols; ++j) {
            C[i][j] = a * AB[i][j] + b * C[i][j];
        }
    }
}

// Explicit template instantiation
template void axpy<float>(float alpha, const std::vector<float>& x, std::vector<float>& y);
template void gemv<float>(float a, const std::vector<std::vector<float>>& A, const std::vector<float>& x, float b, std::vector<float>& y);
template void gemm<float>(float a, const std::vector<std::vector<float>>& A, const std::vector<std::vector<float>>& B, float b, std::vector<std::vector<float>>& C);