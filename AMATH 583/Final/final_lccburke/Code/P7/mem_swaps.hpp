#include <vector>

void swapRows(std::vector<double> &matrix, int nRows, int nCols, int i, int j) {
    for (int k = 0; k < nCols; ++k) {
        std::swap(matrix[i + k * nRows], matrix[j + k * nRows]);
    }
}

void swapCols(std::vector<double> &matrix, int nRows, int nCols, int i, int j) {
    for (int k = 0; k < nRows; ++k) {
        std::swap(matrix[k + i * nRows], matrix[k + j * nRows]);
    }
}
