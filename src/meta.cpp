#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "const.h"
#include "base.h"
#include "regress.h"
#include "lasso.h"
#include "ridge.h"
#include "utils.h"
#include "parse.h"

std::pair<double, double> calcMeta(const size_t &idx = 1) {
    std::cout << "Looking for base function meta-parameters...\n";

    Matrix<double> Xt, Xv, Xs;
    std::vector<double> yt, yv, ys;

    getData(Xt, yt, Xv, yv, Xs, ys);

    std::vector<double> bestFit;
    std::pair<double, double> params;
    double minErr = std::numeric_limits<double>::max();

    std::ofstream dumpFile;
    dumpFile.open(SINE_META);
    dumpFile << std::fixed << std::setprecision(4);

    for (double offset = 0; offset < 2 * M_PI; offset += 0.1) {
        for (double scale = MIN_SCALE; scale < MAX_SCALE; scale += 0.1) {
            // std::cout << "Checking offset = " << offset << ", scale = " << scale << '\n';

            std::function<void(std::vector<double> &)> change = base::metaSin(offset, scale, idx);

            Matrix<double> Xta = applyBase(Xt, change);
            Matrix<double> Xva = applyBase(Xv, change);

            std::vector<double> theta = regress(RIDGE_LAMBDA_MAX, Xta, yt, Xva, yv, ridgeRegression);
            double err = fitness(theta, Xva, yv) / (double)yv.size();
            dumpFile << offset << "\t" << scale << "\t" << err << '\t' << theta << '\n';
            // std::cout << "\tError: " << err << '\n';
            if (err < minErr) {
                params = {offset, scale};
                minErr = err;
                bestFit = theta;
            }
        }
    }
    // std::cout << "Minimum error: " << minErr << "\nBest fit: " << bestFit << '\n';
    dumpFile.close();
    return params;
}