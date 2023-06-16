#include <stdio.h>
#include <math.h>
#include <float.h>

/*
This C++ program finds a practical measure of your machine's SP (32 bit) and DP (64 bit) precision by taking the difference of 2 numbers and comparing the result to zero in each data type. 
*/

int main() {
    // Single Precision (SP - 32-bit)
    float sp_epsilon = 1.0f;
    int sp_counter = 0;

    while (fabsf(1.0f - (1.0f + sp_epsilon)) != 0.0f) {
        sp_epsilon /= 2;
        sp_counter++;
    }

    // Double Precision (DP - 64-bit)
    double dp_epsilon = 1.0;
    int dp_counter = 0;

    while (fabs(1.0 - (1.0 + dp_epsilon)) != 0.0) {
        dp_epsilon /= 2;
        dp_counter++;
    }

    printf("Single Precision (32-bit) Precision: %d bits\n", sp_counter);
    printf("Epsilon: %g\n", sp_epsilon);
    printf("Double Precision (64-bit) Precision: %d bits\n", dp_counter);
    printf("Epsilon: %g\n", dp_epsilon);

    return 0;
}
