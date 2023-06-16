#ifndef PERF_TESTS_HPP
#define PERF_TESTS_HPP

void generate_random_data(int m, int n, std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>& y);
void daxpy_test();
void daxpy_unrolled_test();
void dgemv_test();
void dgemm_test();

#endif // PERF_TESTS_HPP

