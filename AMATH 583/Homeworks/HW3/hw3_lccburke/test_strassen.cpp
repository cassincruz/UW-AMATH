#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include "strassen_mm.hpp"

// Function to generate a random matrix of dimension n
std::vector<std::vector<double>> generateRandomMatrix(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    return matrix;
}

int main(int argc, char* argv[]) {
    int ntrial = std::stoi(argv[1]); // Get ntrials from command line arg

    std::ofstream outFile("results_strassen.txt");

    for (int n = 2; n <= 512; n *= 2) { // Strassen's algorithm requires n to be a power of 2
        double total_time_strassen = 0.0;

        for (int trial = 0; trial < ntrial; ++trial) {
            std::vector<std::vector<double>> A = generateRandomMatrix(n);
            std::vector<std::vector<double>> B = generateRandomMatrix(n);

            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::vector<double>> C = strassen_mm(A, B);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            total_time_strassen += elapsed.count();
        }

        double average_time_strassen = total_time_strassen / ntrial;

        // Output to results_strassen.txt. 
        // Columns: n, average time for strassen
        outFile << n << " " << average_time_strassen << std::endl;
    }

    outFile.close();

    return 0;
}

