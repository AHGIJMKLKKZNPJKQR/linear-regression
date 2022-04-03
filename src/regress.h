#pragma once

#include <vector>
#include <functional>
#include "algebra.h"

std::vector<double> regress(
    const int &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &)> &
);

std::vector<double> regress(
    const int &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &)> &,
    std::ofstream &
);

std::vector<double> regress(
    const int &,
    const int &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &, const double &)> &
);

std::vector<double> regress(
    const int &,
    const int &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const Matrix<double> &, 
    const std::vector<double> &,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &, const double &)> &,
    std::ofstream &
);

double fitness(const std::vector<double> &, const Matrix<double> &, const std::vector<double> &);