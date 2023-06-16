#ifndef TRANSPOSE_HPP
#define TRANSPOSE_HPP

#include <vector>
#include <thread>
#include <iostream>

// Sequential version of the transpose function
void sequentialTranspose(std::vector<int> &matrix, int rows, int cols);

// Threaded version of the transpose function
void threadedTranspose(std::vector<int> &matrix, int rows, int cols, int nthreads);

#endif // TRANSPOSE_HPP