#include <iostream>
#include <vector>
#include <cmath>

double evaluatePolynomial(const std::vector<double>& coefficients, double x) {
    double result = 0;
    for (int i = coefficients.size() - 1; i >= 0; --i) {
        result = result * x + coefficients[i];
    }
    return result;
}

double findRoot(const std::vector<double>& coefficients, double start, double end, double epsilon) {
    double mid;
    while (end - start >= epsilon) {
        mid = (start + end) / 2;
        if (std::abs(evaluatePolynomial(coefficients, mid)) < epsilon) {
            return mid;
        } else if (evaluatePolynomial(coefficients, start) * evaluatePolynomial(coefficients, mid) < 0) {
            end = mid;
        } else {
            start = mid;
        }
    }
    return mid;
}

int main() {
    int degree;
    std::cout << "Enter the degree of the polynomial: ";
    std::cin >> degree;

    std::vector<double> coefficients(degree + 1);
    for (int i = degree; i >= 0; --i) {
        std::cout << "Enter coefficient " << i << ": ";
        std::cin >> coefficients[i];
    }

    double start, end;
    std::cout << "Enter the start of the domain: ";
    std::cin >> start;
    std::cout << "Enter the end of the domain: ";
    std::cin >> end;

    for (double x = start; x <= end; x += 0.5) {
        if (std::abs(evaluatePolynomial(coefficients, x)) < 0.00001) {
            std::cout << "Root found: " << x << std::endl;
        }
        else if (evaluatePolynomial(coefficients, x) * evaluatePolynomial(coefficients, x + 0.5) <= 0) {
            double root = findRoot(coefficients, x, x + 0.5, 0.00001);
            if (std::abs(evaluatePolynomial(coefficients, root)) < 0.00001) {
                std::cout << root << std::endl;
            }
        }
    }

    return 0;
}
