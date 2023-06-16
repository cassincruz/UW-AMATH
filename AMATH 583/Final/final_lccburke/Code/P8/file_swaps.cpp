// file_swaps.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <chrono>
#include "file_swaps.hpp"

std::pair<int, int> getRandomIndices(int n)
{
    int i = std::rand() % n;
    int j = std::rand() % (n - 1);
    if (j >= i)
    {
        j++;
    }
    return std::make_pair(i, j);
}

int main(int argc, char *argv[])
{
    // Set the random seed
    std::srand(std::time(0));

    // Test for different dimensions
    for (int n = 16; n <= 16384; n *= 2) {
        // Create a matrix
        std::vector<double> matrix(n * n);

        // Fill the matrix with some values
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[j * n + i] = i * n + j;
            }
        }

        // Write the matrix to a file
        std::string filename = "matrix.bin";
        std::fstream file(filename, std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<char *>(&matrix[0]), n * n * sizeof(double));
        file.close();

        // Get random indices
        std::pair<int, int> rowIndices = getRandomIndices(n);
        std::pair<int, int> colIndices = getRandomIndices(n);

        // Open the file in read-write mode for swapping
        std::fstream fileToSwap(filename, std::ios::in | std::ios::out | std::ios::binary);

        // Measure the time required for row swapping using file I/O
        auto startTime = std::chrono::high_resolution_clock::now();
        swapRowsInFile(fileToSwap, n, n, rowIndices.first, rowIndices.second);
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;
        std::cout << "n = " << n << ", row swap time = " << duration.count() << " seconds" << std::endl;

        // Measure the time required for column swapping using file I/O
        startTime = std::chrono::high_resolution_clock::now();
        swapColsInFile(fileToSwap, n, n, colIndices.first, colIndices.second);
        endTime = std::chrono::high_resolution_clock::now();
        duration = endTime - startTime;
        std::cout << "n = " << n << ", column swap time = " << duration.count() << " seconds" << std::endl;

        // Close the file after swapping
        fileToSwap.close();

        // Delete the test file after each problem size
        std::remove(filename.c_str());
    }

    return 0;
}
