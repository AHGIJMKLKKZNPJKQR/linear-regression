#include "utils.h"

void minCoord(std::vector<double> &v, const int &idx, const std::function<double(const double &)> &df) {
    double a = INIT_GRAD, change;
    while (true) {
        for (int i = 0; i < MAX_ITER; ++i) {
            if ((change = abs(df(v[idx]))) < EPS)
                return;
            v[idx] -= a * change;
        }
        a *= GRAD_PARAM;
    }
}

// df(x) returns norm of derivative at x and updates v
void gradient(std::vector<double> &v, const std::function<double(std::vector<double> &, const double &a)> &df) {
    double a = INIT_GRAD;
    while (true) {
        std::vector<double> vcpy(v);
        for (int i = 0; i < MAX_ITER; ++i)
            if (df(vcpy, a) < EPS) {
                v = vcpy;
                return;
            }
        a *= GRAD_PARAM;
    }
}

double norm1(const std::vector<double> &v) {
    double sum = 0;
    for (const double &i : v)
        sum += abs(i);
    return sum;
}

double norm2(const std::vector<double> &v) {
    double sum = 0;
    for (const double &i : v)
        sum += i * i;
    return sum;
}