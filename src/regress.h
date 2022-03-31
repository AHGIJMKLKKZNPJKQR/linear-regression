#pragma once

#include <vector>
#include <functional>
#include "algebra.h"

std::vector<double> regress(
    const Matrix<double> &, 
    const std::vector<double> &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &)> &
);

double fitness(const std::vector<double> &, const Matrix<double> &, const std::vector<double> &);