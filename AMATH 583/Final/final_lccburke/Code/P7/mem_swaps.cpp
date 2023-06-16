#include <iostream>
#include <vector>
#include <utility>   // For std::pair
#include <cstdlib>   // For std::rand()
#include <ctime>     // For std::time()
#include <chrono>    // For std::chrono
#include "mem_swaps.hpp"

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

int main() {
    // Set the random seed
    std::srand(std::time(0));

    // Number of trials
    int ntrials = 3;

    // Test for different dimensions
    for (int n = 16; n <= 16384; n *= 2) {
        // Total time for all trials
        std::chrono::duration<double> total_time(0);

        for (int t = 0; t < ntrials; ++t) {
            // Create a matrix
            std::vector<double> matrix(n * n);

            // Fill the matrix with some values
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    matrix[j * n + i] = i * n + j;
                }
            }

            // Get random indices
            std::pair<int, int> rowIndices = getRandomIndices(n);
            std::pair<int, int> colIndices = getRandomIndices(n);

            // Start the clock
            auto start_time = std::chrono::high_resolution_clock::now();

            // Swap rows
            swapRows(matrix, n, n, rowIndices.first, rowIndices.second);

            // Swap columns
            swapCols(matrix, n, n, colIndices.first, colIndices.second);

            // Stop the clock
            auto end_time = std::chrono::high_resolution_clock::now();

            // Add the time for this trial to the total time
            total_time += end_time - start_time;
        }

        // Compute the average time
        double avg_time = total_time.count() / ntrials;

        // Print the results
        std::cout << "n = " << n << ", avg time = " << avg_time << " seconds\n";
    }

    return 0;
}
