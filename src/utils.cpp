#include "utils.h"
#include "const.h"

void coordDescent(std::vector<double> &v, const std::function<double(std::vector<double> &, const size_t &)> &updateFunc) {
    double maxdiff = std::numeric_limits<double>::max();
    while (maxdiff > EPS) {
        maxdiff = 0;
        for (size_t i = 0; i < v.size(); ++i)
            maxdiff = std::max(abs(updateFunc(v, i)), maxdiff);
    }
}

// df(x) returns norm of derivative at x and updates v
void gradient(
    std::vector<double> &v, 
    const std::function<double(std::vector<double> &, const double &a)> &df
) {
    double a = INIT_GRAD;
    while (true) {
        std::vector<double> vcpy(v);
        for (int i = 0; i < MAX_ITER; ++i) {
            if (df(vcpy, a) < EPS) {
                v = vcpy;
                return;
            }
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