template<typename T>
void mm_kij(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n) {
    if (A.size() != m * p || B.size() != p * n || C.size() != m * n) {
        throw std::invalid_argument("The dimensions of the matrices do not match.");
    }

    std::vector<T> AB(m * n, 0);

    for (int k = 0; k < p; ++k) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                AB[j + i*n] += A[k + i*p] * B[j + k*n];
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            C[j + i*n] = a * AB[j + i*n] + b * C[j + i*n];
        }
    }

}