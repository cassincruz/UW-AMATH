#include <iostream>

int main() {
    // Using Single Precision (SP - 32-bit) floating-point numbers
    int a = 200.0;
    int b = 300.0;
    int c = 400.0;
    int d = 500.0;

    int result_sp = a * b * c * d;
    std::cout << "Result: " << result_sp << std::endl;
    return 0;
}
