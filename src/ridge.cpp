#include <functional>
#include "utils.h"
#include "ridge.h"
#include <iostream>

std::function<double(std::vector<double> &, const double &)> quadratic_gradient(const Matrix<double> &X, const std::vector<double> &y, const double &lambda) {
    Matrix<double> Z = X.transpose() * X;
    std::vector<double> C = X.transpose() * y;

    return [&](std::vector<double> &theta, const double &a) {
        std::vector<double> grad = X.transpose() * X * theta + lambda * theta - X.transpose() * y;
        theta = theta - a * grad;
        return norm2(grad);
    };
}

std::vector<double> ridgeRegression(const Matrix<double> &X, const std::vector<double> &y, const double &lambda) {
    std::vector<double> theta(X.getM(), 0);
    gradient(theta, quadratic_gradient(X, y, lambda));
    return theta;
}