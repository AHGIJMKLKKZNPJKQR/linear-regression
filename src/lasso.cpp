#include <functional>
#include "lasso.h"
#include "utils.h"

std::function<double(std::vector<double> &, const size_t &)> lassoUpdate(const Matrix<double> &X, const std::vector<double> &y, const double &lambda) {
    return [&](std::vector<double> &v, const size_t &idx) -> double {
        double a = 0, c = 0;
        for (size_t i = 0; i < X.getN(); ++i)
            a += X[i][idx] * X[i][idx];
        a *= 2;
        for (size_t i = 0; i < X.getN(); ++i) {
            double part = y[i] + v[idx] * X[i][idx];
            for (size_t j = 0; j < X.getM(); ++j)
                part -= v[j] * X[i][j];
            c += part * X[i][idx];
        }
        c *= 2;
        double save = v[idx];

        if (idx == 0) {
            v[idx] = c / a;
            return v[idx] - save;
        }

        if (c < -lambda * X.getM())
            v[idx] = (c + lambda * X.getM()) / a;
        else if (c > lambda * X.getM())
            v[idx] = (c - lambda * X.getM()) / a;
        else v[idx] = 0;

        return v[idx] - save;
    };
}

std::vector<double> lassoRegression(const Matrix<double> &X, const std::vector<double> &y, const double &lambda) {
    std::vector<double> theta(X.getM(), 0);
    coordDescent(theta, lassoUpdate(X, y, lambda));
    return theta;
}