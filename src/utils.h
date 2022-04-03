#pragma once

#include <functional>
#include <vector>
#include <iostream>

void coordDescent(std::vector<double> &, const std::function<double(std::vector<double> &, const size_t &)> &);
void gradient(std::vector<double> &, const std::function<double(std::vector<double> &, const double &)> &);
double norm1(const std::vector<double> &);
double norm2(const std::vector<double> &);


template <typename T>
double abs(const T &a) {
    return a < 0 ? -a : a;
}

// This has to go first
template <typename T>
std::ostream & operator<<(std::ostream &os, const std::vector<std::vector<T>> &v) {
    for (const std::vector<T> &i : v)
        os << i << '\n';
    return os;
}

// This has to go second
template <typename T>
std::ostream & operator<<(std::ostream &os, const std::vector<T> &v) {
    for (const T &i : v)
        os << i << '\t';
    return os;
}

template <typename T>
std::istream & operator>>(std::istream &is, std::vector<T> &v) {
    for (T &i : v)
        is >> i;
    return is;
}