#pragma once

#include <vector>
#include <functional>
#include <string>
#include "algebra.h"

struct baseChange {
    std::function<void(std::vector<double> &)> func;
    std::string name;
};

Matrix<double> applyBase(Matrix<double>, std::function<void(std::vector<double> &)>);

namespace base {
    void sin(std::vector<double> &);
    void sqrt(std::vector<double> &);
    void sig(std::vector<double> &);
    std::function<void(std::vector<double> &)> pow(const double &k);
    std::function<void(std::vector<double> &)> gauss(const double &k);
    std::function<void(std::vector<double> &)> metaSin(const double &offset, const double &scale, const size_t &idx = 1);

    std::function<void(std::vector<double> &)> generic(const std::vector<std::function<double(const double &)>> &);
}