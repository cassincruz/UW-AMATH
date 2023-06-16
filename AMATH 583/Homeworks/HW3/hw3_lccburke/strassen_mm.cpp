#include <vector>
#include <iostream>

template <typename T>
std::vector<std::vector<T>> add(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B)
{
    int n = A.size();
    std::vector<std::vector<T>> C(n, std::vector<T>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

template <typename T>
std::vector<std::vector<T>> subtract(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B)
{
    int n = A.size();
    std::vector<std::vector<T>> C(n, std::vector<T>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

template <typename T>
std::vector<std::vector<T>> strassen_mm(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B)
{
    int n = A.size();

    if (n == 1)
    {
        return std::vector<std::vector<T>>{{A[0][0] * B[0][0]}};
    }
    else
    {
        int newSize = n / 2;
        std::vector<std::vector<T>> a11(newSize, std::vector<T>(newSize));
        std::vector<std::vector<T>> a12(newSize, std::vector<T>(newSize));
        std::vector<std::vector<T>> a21(newSize, std::vector<T>(newSize));
        std::vector<std::vector<T>> a22(newSize, std::vector<T>(newSize));

        std::vector<std::vector<T>> b11(newSize, std::vector<T>(newSize));
        std::vector<std::vector<T>> b12(newSize, std::vector<T>(newSize));
        std::vector<std::vector<T>> b21(newSize, std::vector<T>(newSize));
        std::vector<std::vector<T>> b22(newSize, std::vector<T>(newSize));

        // Fill in the sub-matrices
        for (int i = 0; i < newSize; i++)
        {
            for (int j = 0; j < newSize; j++)
            {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + newSize];
                a21[i][j] = A[i + newSize][j];
                a22[i][j] = A[i + newSize][j + newSize];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + newSize];
                b21[i][j] = B[i + newSize][j];
                b22[i][j] = B[i + newSize][j + newSize];
            }
        }

        std::vector<std::vector<T>> p1 = strassen_mm(a11, subtract(b12, b22));
        std::vector<std::vector<T>> p2 = strassen_mm(add(a11, a12), b22);
        std::vector<std::vector<T>> p3 = strassen_mm(add(a21, a22), b11);
        std::vector<std::vector<T>> p4 = strassen_mm(a22, subtract(b21, b11));
        std::vector<std::vector<T>> p5 = strassen_mm(add(a11, a22), add(b11, b22));
        std::vector<std::vector<T>> p6 = strassen_mm(subtract(a12, a22), add(b21, b22));
        std::vector<std::vector<T>> p7 = strassen_mm(subtract(a11, a21), add(b11, b12));

        std::vector<std::vector<T>> c11 = add(subtract(add(p5, p4), p2), p6);
        std::vector<std::vector<T>> c12 = add(p1, p2);
        std::vector<std::vector<T>> c21 = add(p3, p4);
        std::vector<std::vector<T>> c22 = subtract(subtract(add(p5, p1), p3), p7);

        std::vector<std::vector<T>> C(n, std::vector<T>(n));

        for (int i = 0; i < newSize; i++)
        {
            for (int j = 0; j < newSize; j++)
            {
                C[i][j] = c11[i][j];
                C[i][j + newSize] = c12[i][j];
                C[i + newSize][j] = c21[i][j];
                C[i + newSize][j + newSize] = c22[i][j];
            }
        }

        return C;
    }
}

