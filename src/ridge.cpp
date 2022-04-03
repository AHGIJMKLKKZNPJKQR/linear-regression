#include <functional>
#include "utils.h"
#include "ridge.h"
#include <iostream>

std::function<double(std::vector<double> &, const double &)> quadratic_gradient(const Matrix<double> &X, const std::vector<double> &y, const double &lambda) {
    return [&](std::vector<double> &theta, const double &a) {
        std::vector<double> grad = X.transpose() * X * theta + lambda * theta - X.transpose() * y;
        theta = theta - a * grad;
        return norm2(grad);
    };
}



std::vector<double> ridgeRegression(const Matrix<double> &X, const std::vector<double> &y, const double &lambda) {
    Matrix<double> I = Id<double>(X.getM());
    I[0][0] = 0;
    return (X.transpose() * X + lambda * I).inverse() * X.transpose() * y;
}