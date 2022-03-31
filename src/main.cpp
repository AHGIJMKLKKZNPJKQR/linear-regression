#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

#include "const.h"
#include "utils.h"
#include "ridge.h"
#include "regress.h"
#include "parse.h"

int main() {
    Matrix<double> Xt, Xv, Xs;
    std::vector<double> yt, yv, ys;

    getData(Xt, yt, Xv, yv, Xs, ys);

    std::cout << "RIDGE REGRESSION:\n";
    std::vector<double> theta = regress(Xt, yt, Xv, yv, ridgeRegression);
    std::cout << "Average error squared: " << fitness(theta, Xs, ys) / (double)ys.size() << '\n';
    std::cout << "Parameters: " << theta << '\n';
}