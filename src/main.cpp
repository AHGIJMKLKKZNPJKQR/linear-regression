#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

#include "const.h"
#include "utils.h"
#include "ridge.h"
#include "regress.h"
#include "parse.h"

double fitness2(std::vector<double> &theta, Matrix<double> &X, std::vector<double> &y) {
    std::vector<double> err = X * theta;
    for (int i = 0; i < err.size(); ++i)
        std::cout << "Prediction: " << err[i] << ", Actual: " << y[i] << '\n';
    return fitness(theta, X, y);
}

int main() {
    Matrix<double> Xt, Xv, Xs;
    std::vector<double> yt, yv, ys;

    getData(Xt, yt, Xv, yv, Xs, ys);
    // applyBase(Xt, [](const double & x) { return exp(-x*x/2); });
    // applyBase(Xv, [](const double & x) { return exp(-x*x/2); });
    // applyBase(Xs, [](const double & x) { return exp(-x*x/2); });

    std::cout << "RIDGE REGRESSION:\n";
    std::vector<double> theta = regress(Xt, yt, Xv, yv, ridgeRegression);
    std::cout << "Average error squared: " << fitness(theta, Xs, ys) / (double)ys.size() << '\n';
    std::cout << "Parameters: " << theta << '\n';
}