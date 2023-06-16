#include <iostream>
#include "hw3_p1_header.hpp"

void printMatrix(const std::vector<double>& matrix, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << matrix[j + i*n] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    double a = 1.0, b = 0.0;
    int m = 2, p = 2, n = 2;

    std::vector<double> A = {1, 2, 3, 4}; // A 2x2 matrix
    std::vector<double> B = {5, 6, 7, 8}; // A 2x2 matrix
    std::vector<double> C(m * n, 0); // A 2x2 matrix initialized with zeros

    mm_ijk(a, A, B, b, C, m, p, n);
    printMatrix(C, m, n);

    // Reset C
    std::fill(C.begin(), C.end(), 0);
    mm_jki(a, A, B, b, C, m, p, n);
    printMatrix(C, m, n);

    // Reset C
    std::fill(C.begin(), C.end(), 0);
    mm_kij(a, A, B, b, C, m, p, n);
    printMatrix(C, m, n);

    // Reset C
    std::fill(C.begin(), C.end(), 0);
    mm_jik(a, A, B, b, C, m, p, n);
    printMatrix(C, m, n);

    // Reset C
    std::fill(C.begin(), C.end(), 0);
    mm_ikj(a, A, B, b, C, m, p, n);
    printMatrix(C, m, n);

    // Reset C
    std::fill(C.begin(), C.end(), 0);
    mm_kji(a, A, B, b, C, m, p, n);
    printMatrix(C, m, n);

    return 0;
}

