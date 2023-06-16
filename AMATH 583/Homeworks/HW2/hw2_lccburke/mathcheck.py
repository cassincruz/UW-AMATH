import numpy as np

# Test axpy
x = np.array([1.0, 2.0, 3.0], dtype=np.float32)
y = np.array([4.0, 5.0, 6.0], dtype=np.float32)
alpha = np.float32(2.0)

result_axpy = alpha * x + y
print("Result of axpy (float):")
print(result_axpy)

# Test gemv
A = np.array([[1, 2, 3], [4, 5, 6]], dtype=np.float32)
x_gemv = np.array([1, 2, 3], dtype=np.float32)
y_gemv = np.array([1, 1], dtype=np.float32)
a_gemv = np.float32(1.0)
b_gemv = np.float32(0.0)

result_gemv = a_gemv * np.dot(A, x_gemv) + b_gemv * y_gemv
print("\nResult of gemv (float):")
print(result_gemv)

# Test gemm
A_gemm = np.array([[1, 2], [3, 4]], dtype=np.float32)
B_gemm = np.array([[2, 0], [1, 2]], dtype=np.float32)
C_gemm = np.zeros((2, 2), dtype=np.float32)
a_gemm = np.float32(1.0)
b_gemm = np.float32(0.0)

result_gemm = a_gemm * np.dot(A_gemm, B_gemm) + b_gemm * C_gemm
print("\nResult of gemm (float):")
print(result_gemm)

