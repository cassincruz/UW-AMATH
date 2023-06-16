# AMATH 483/583 HW2
Author: Lucas Cassin Cruz Burke

See amath483_583_hw2.pdf for problem details. 

## Problem 1

- Function file: daxpy.cpp
- Main source file: daxpy_main.cpp
- Performance plot: Fig1.png

### Compilation steps
To run daxpy_main.cpp and test the performance of daxpy.cpp you can run the following:
>>> g++ -std=c++11 daxpy_main.cpp daxpy.cpp refBLAS.hpp

## Problem 2

- Function file: daxpy_unroll.cpp
- Main source file: daxpy_unroll_main.cpp
- Performance plot: Fig2.png

### Compilation steps
To run daxpy_unroll_main.cpp and test the performance of daxpy_unroll.cpp you can run the following:
>>> g++ -std=c++11 daxpy_unroll_main.cpp daxpy_unroll.cpp refBLAS.hpp

## Problem 3

- Function file: dgemv.cpp
- Main source file: dgemv_main.cpp
- Performance plot: Fig3.png

### Compilation steps 
To run dgemv_main.cpp and test the performance of dgemv.cpp you can run the following:
>>> g++ -std=c++11 dgemv_main.cpp dgemv.cpp refBLAS.hpp

## Problem 4

- Function file: dgemm.cpp
- Main source file: dgemm_main.cpp
- Performance plot: Fig4.png

### Compilation steps
To run dgemm_main.cpp and test the performance of dgemm.cpp you can run the following:
>>> g++ -std=c++11 dgemm_main.cpp dgemm.cpp refBLAS.hpp

## Problem 5

- Function file: refBLAS.cpp
- Main source file: template_main.cpp
- Peformance plot: Fig5.png

### Compilation steps
To run template_main.cpp and test the performance of axpy, gemv and gemm using floats you can run the following:
>>> g++ -std=c++11 template_main.cpp refBLAS.cpp refBLAS.hpp

## Problem 6
For this problem we can use the above template_main.cpp to test our shared object library librefBLAS.so.

- Function file: template_main.cpp
- Header file: refBLAS.hpp

### Compilation steps
To run template_main.cpp and demonstrate the usage of the shared object library librefBLAS.so use the following:
>>> g++ -std=c++11 -o template_main template_main.cpp -L. -lrefBLAS
