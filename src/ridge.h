#pragma once

#include <vector>
#include "algebra.h"

// finds arg min { ||X*theta - y||^2 + lambda * ||theta||^2 }
std::vector<double> ridgeRegression(const Matrix<double> &, const std::vector<double> &, const double &);