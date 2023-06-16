#include <iostream>
#include <cmath>
#include <limits>

int main() {
    // Single Precision (SP - 32-bit)
    float sp_epsilon = 1.0f;
    int sp_counter = 0;

    while (std::abs(1.0f - (1.0f + sp_epsilon)) != 0.0f) {
        sp_epsilon /= 2;
        sp_counter++;
    }

    // Double Precision (DP - 64-bit)
    double dp_epsilon = 1.0;
    int dp_counter = 0;

    while (std::abs(1.0 - (1.0 + dp_epsilon)) != 0.0) {
        dp_epsilon /= 2;
        dp_counter++;
    }

    std::cout << "Single Precision (32-bit) Precision: " << sp_counter << " bits" << std::endl;
    std::cout << "Epsilon: " << sp_epsilon << std::endl;
    std::cout << "Double Precision (64-bit) Precision: " << dp_counter << " bits" << std::endl;
    std::cout << "Epsilon: " << dp_epsilon << std::endl;

    return 0;
}
