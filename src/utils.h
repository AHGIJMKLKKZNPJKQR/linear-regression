#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <vector>
#include <cmath>
#include "const.h"

void minCoord(std::vector<double> &, const int &idx, const std::function<double(const double &)> &df);
void gradient(std::vector<double> &, const std::function<double(std::vector<double> &, const double &)> &);
double norm1(const std::vector<double> &);
double norm2(const std::vector<double> &);

#endif