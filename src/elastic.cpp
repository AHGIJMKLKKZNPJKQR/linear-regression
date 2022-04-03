#include <vector>
#include <functional>
#include "algebra.h"
#include "utils.h"

std::function<double(std::vector<double> &, const size_t &)> elasticNetUpdate(const Matrix<double> &X, const std::vector<double> &y, const double &l1, const double &l2) {
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
        a += l2 + l2;

        if (c < -l1)
            v[idx] = (c + l1) / a;
        else if (c > l1)
            v[idx] = (c - l1) / a;
        else v[idx] = 0;

        return v[idx] - save;
    };
}

std::vector<double> elasticNetRegression(const Matrix<double> &X, const std::vector<double> &y, const double &l1, const double &l2) {
    std::vector<double> theta(X.getM(), 0);
    coordDescent(theta, elasticNetUpdate(X, y, l1, l2));
    return theta;
}
