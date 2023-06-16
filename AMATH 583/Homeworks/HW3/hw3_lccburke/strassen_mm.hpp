#ifndef STRASSEN_HPP
#define STRASSEN_HPP

#include <vector>

template<typename T>
std::vector<std::vector<T>> add(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);

template<typename T>
std::vector<std::vector<T>> subtract(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);

template<typename T>
std::vector<std::vector<T>> strassen_mm(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);

#include "strassen_mm.cpp"

#endif // STRASSEN_HPP

