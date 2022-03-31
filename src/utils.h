#pragma once

#include <functional>
#include <vector>
#include <iostream>

void minCoord(std::vector<double> &, const int &idx, const std::function<double(const double &)> &df);
void gradient(std::vector<double> &, const std::function<double(std::vector<double> &, const double &)> &);
double norm1(const std::vector<double> &);
double norm2(const std::vector<double> &);


template <typename T>
double abs(const T &a) {
    return a < 0 ? -a : a;
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const std::vector<T> &v) {
    for (const T &i : v)
        os << i << ' ';
    return os;
}

template <typename T>
std::istream & operator>>(std::istream &is, std::vector<T> &v) {
    for (T &i : v)
        is >> i;
    return is;
}