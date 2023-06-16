#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include "hw3_p1_header.hpp"

// Function to generate a random matrix of dimension n
std::vector<float> generateRandomMatrix(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    std::vector<float> matrix(n * n);
    for (int i = 0; i < n * n; ++i) {
        matrix[i] = dis(gen);
    }

    return matrix;
}

int main(int argc, char* argv[]) {
    int ntrial = std::stoi(argv[1]); // Get ntrials from command line arg

    std::ofstream outFile("results_float.txt");

    for (int n = 2; n <= 512; ++n) {
        float total_time_kij = 0.0;
        float total_time_jki = 0.0;

        for (int trial = 0; trial < ntrial; ++trial) {
            std::vector<float> A = generateRandomMatrix(n);
            std::vector<float> B = generateRandomMatrix(n);
            std::vector<float> C(n * n);

            auto start = std::chrono::high_resolution_clock::now();
            mm_kij(1.0f, A, B, 1.0f, C, n, n, n);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = end - start;
            total_time_kij += elapsed.count();

            start = std::chrono::high_resolution_clock::now();
            mm_jki(1.0f, A, B, 1.0f, C, n, n, n);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            total_time_jki += elapsed.count();
        }

        float average_time_kij = total_time_kij / ntrial;
        float average_time_jki = total_time_jki / ntrial;

        // Output to results_float.txt. 
        // Columns: n, average time for kij, average time for jki

        outFile << n << " " << average_time_kij << " " << average_time_jki << std::endl;
    }

    outFile.close();

    return 0;
}

