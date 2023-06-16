// file_swaps.hpp
#include <fstream>
#include <vector>

void swapRowsInFile(std::fstream &file, int nRows, int nCols, int i, int j) {
    // Create buffers for the rows
    std::vector<double> row1(nCols), row2(nCols);

    // Seek to the start of each row
    file.seekg(i * nCols * sizeof(double));
    file.read(reinterpret_cast<char*>(&row1[0]), nCols * sizeof(double));
    file.seekg(j * nCols * sizeof(double));
    file.read(reinterpret_cast<char*>(&row2[0]), nCols * sizeof(double));

    // Swap the rows
    file.seekp(i * nCols * sizeof(double));
    file.write(reinterpret_cast<char*>(&row2[0]), nCols * sizeof(double));
    file.seekp(j * nCols * sizeof(double));
    file.write(reinterpret_cast<char*>(&row1[0]), nCols * sizeof(double));
}

void swapColsInFile(std::fstream &file, int nRows, int nCols, int i, int j) {
    // Create buffers for the columns
    std::vector<double> col1(nRows), col2(nRows);

    // Read each column
    for (int row = 0; row < nRows; ++row) {
        file.seekg((row * nCols + i) * sizeof(double));
        file.read(reinterpret_cast<char*>(&col1[row]), sizeof(double));
        file.seekg((row * nCols + j) * sizeof(double));
        file.read(reinterpret_cast<char*>(&col2[row]), sizeof(double));
    }

    // Swap the columns
    for (int row = 0; row < nRows; ++row) {
        file.seekp((row * nCols + i) * sizeof(double));
        file.write(reinterpret_cast<char*>(&col2[row]), sizeof(double));
        file.seekp((row * nCols + j) * sizeof(double));
        file.write(reinterpret_cast<char*>(&col1[row]), sizeof(double));
    }
}