
#include "transpose.hpp"

// Sequential version of the transpose function
void sequentialTranspose(std::vector<int> &matrix, int rows, int cols) {
    std::vector<int> transpose(rows * cols);
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            transpose[x * rows + y] = matrix[y * cols + x];
        }
    }
    matrix = transpose;
}

// Function that each thread will run to compute the transpose
void threadFunction(std::vector<int> &matrix, std::vector<int> &transpose, int startRow, int endRow, int cols, int totalRows) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < cols; ++j) {
            transpose[j * totalRows + i] = matrix[i * cols + j];
        }
    }
}

// Threaded version of the transpose function
void threadedTranspose(std::vector<int> &matrix, int rows, int cols, int nthreads) {
    std::vector<int> transpose(rows * cols);
    std::vector<std::thread> threads;

    int rowsPerThread = rows / nthreads;
    for (int i = 0; i < nthreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == nthreads - 1) ? rows : startRow + rowsPerThread;
        threads.emplace_back(threadFunction, std::ref(matrix), std::ref(transpose), startRow, endRow, cols, rows);
    }

    // Wait for all threads to finish
    for (std::thread &th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    matrix = transpose;
}

// Main function to test the transpose functions
int main() {
    // Create a matrix
    int rows = 3, cols = 3;
    std::vector<int> matrix = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Print the matrix
    std::cout << "M: " << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[j * rows + i] << " ";
        }
        std::cout << std::endl;
    }

    // Compute the transpose sequentially
    sequentialTranspose(matrix, rows, cols);

    // Print the transpose
    std::cout << "Sequential: " << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[j * rows + i] << " ";
        }
        std::cout << std::endl;
    }

    // Reset the matrix
    matrix = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Compute the transpose using threads
    threadedTranspose(matrix, rows, cols, 2);

    // Print the transpose
    std::cout << "Threaded: " << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[j * rows + i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
