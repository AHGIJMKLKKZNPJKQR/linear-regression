#pragma once

#include <vector>
#include "algebra.h"
#include <functional>

void getData(
    Matrix<double> &, std::vector<double> &,
    Matrix<double> &, std::vector<double> &,
    Matrix<double> &, std::vector<double> &
);

std::vector<std::pair<double, double>> normalizationParams(const Matrix<double> &);
void normalize(Matrix<double> &, std::vector<std::pair<double, double>> &);
void applyBase(Matrix<double> &, const std::function<double(const double &)> &);