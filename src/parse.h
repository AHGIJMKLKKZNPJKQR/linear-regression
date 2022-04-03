#pragma once

#include <vector>
#include "algebra.h"
#include <functional>

void getData(
    Matrix<double> &, std::vector<double> &,
    Matrix<double> &, std::vector<double> &,
    Matrix<double> &, std::vector<double> &,
    const int & = SEED
);

std::vector<std::pair<double, double>> normalizationParams(const Matrix<double> &);
void normalize(Matrix<double> &, std::vector<std::pair<double, double>> &);

std::vector<std::pair<double, double>> standardizationParams(const Matrix<double> &);
void standardize(Matrix<double> &, std::vector<std::pair<double, double>> &);