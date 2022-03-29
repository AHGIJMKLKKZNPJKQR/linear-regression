#include <vector>
#include <iostream>
#include "ridge.h"
#include <cstdlib>

int main() {
    Matrix<double> X(4, 5);
    std::vector<double> y(4);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 5; ++j)
            X[i][j] = 1;
    
    for (int i = 0; i < 4; ++i)
        y[i] = 2;

    double lambda = 10;
    std::vector<double> theta = ridgeRegression(X, y, lambda);
    for (double &i : theta)
        std::cout << i << '\n';
}