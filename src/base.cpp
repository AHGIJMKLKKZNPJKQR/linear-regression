#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

#include "base.h"


Matrix<double> applyBase(Matrix<double> X, std::function<void(std::vector<double> &)> transform) {
    for (size_t i = 0; i < X.getN(); ++i)
        transform(X[i]);
    return X;
}

namespace base {
    void sin(std::vector<double> &v) {
        for (size_t i = 1; i < v.size(); ++i)
            v[i] = ::sin(v[i]);
    }

    void sqrt(std::vector<double> &v) {
        for (size_t i = 1; i < v.size(); ++i)
            v[i] = (v[i] < 0 ? -::sqrt(-v[i]) : ::sqrt(v[i]));
    }

    void sig(std::vector<double> &v) {
        for (size_t i = 1; i < v.size(); ++i)
            v[i] = 1.0 / (1.0 + exp(-v[i]));
    }

    std::function<void(std::vector<double> &)> generic(const std::vector<std::function<double(const double &)>> &funcs) {
        return [=](std::vector<double> &v) -> void {
            for (size_t i = 1; i < v.size(); ++i)
                v[i] = funcs[i - 1](v[i]);
        };
    }

    std::function<void(std::vector<double> &)> pow(const double &k) {
        return [=](std::vector<double> &v) -> void {
            for (size_t i = 1; i < v.size(); ++i)
                v[i] = ::pow(v[i], k);
        };
    }
    

    std::function<void(std::vector<double> &)> gauss(const double &k) {
        return [=](std::vector<double> &v) -> void {
            double avg = 0;
            for (size_t i = 1; i < v.size(); ++i)
                avg += v[i];
            avg /= (double)(v.size() - 1);
            for (size_t i = 1; i < v.size(); ++i)
                v[i] = ::exp(-(v[i] - avg) * (v[i] - avg) / (2.0 * k));
        };
    }

    std::function<void(std::vector<double> &)> metaSin(const double &offset, const double &scale, const size_t &idx) {
        return [=](std::vector<double> &v) -> void {
            v[idx] = ::sin(scale * (v[idx] - offset));
        };
    }
}