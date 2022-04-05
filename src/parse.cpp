#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "utils.h"
#include "const.h"
#include "parse.h"  

void fill(
    Matrix<double> &X, 
    std::vector<double> &y, 
    std::vector<std::vector<double>>::iterator &from, 
    const std::vector<std::vector<double>>::iterator &to
) {
    while (from != to) {
        y.push_back(from->back());
        from->pop_back();
        X.addRow(*from);
        ++from;
    }
}

void dump(const Matrix<double> &X, const std::vector<double> &y, std::ofstream &dumpFile) {
    for (size_t i = 0; i < X.getN(); ++i)
        dumpFile << X[i] << '\t' << y[i] << '\n';
}

void getData(
    Matrix<double> &Xt, std::vector<double> &yt,
    Matrix<double> &Xv, std::vector<double> &yv,
    Matrix<double> &Xs, std::vector<double> &ys,
    const int &seed
) {
    std::ifstream data;
    data.open(DATA_PATH);

    std::vector<std::vector<double>> input;

    std::vector<double> row(8, 1);

    while (data) {
        for (int i = 1; i < 8; ++i)
            data >> row[i];
        // data >> row;
        input.push_back(row);
    }
    data.close();

    srand(seed);
    std::random_shuffle(input.begin(), input.end());
    
    Xt.clear(), yt.clear(), Xv.clear(), yv.clear(), Xs.clear(), ys.clear();
    std::vector<std::vector<double>>::iterator from = input.begin();
    fill(Xt, yt, from, from + (size_t)((double)input.size() * TRAINING_SIZE));
    fill(Xv, yv, from, from + (size_t)((double)input.size() * VALIDATION_SIZE));
    fill(Xs, ys, from, input.end());

    // std::vector<std::pair<double, double>> params = normalizationParams(Xt);
    std::vector<std::pair<double, double>> params = standardizationParams(Xt);
    // normalize(Xt, params);
    // normalize(Xv, params);
    // normalize(Xs, params);
    standardize(Xt, params);
    standardize(Xv, params);
    standardize(Xs, params);
    std::ofstream dumpFile;
    // dumpFile.open(NORMALIZED_DATA_FILE);
    dumpFile.open(STANDARDIZED_DATA_FILE);
    dumpFile << std::fixed << std::setprecision(4);
    dump(Xt, yt, dumpFile);
    dump(Xv, yv, dumpFile);
    dump(Xs, ys, dumpFile);
    dumpFile.close();
}

std::vector<std::pair<double, double>> normalizationParams(const Matrix<double> &X) {
    std::vector<std::pair<double, double>> params(X.getM(), {0, 0});
    // Average
    for (size_t i = 0; i < X.getN(); ++i)
        for (size_t j = 1; j < X.getM(); ++j)
            params[j].first += X[i][j];
    for (size_t i = 0; i < params.size(); ++i)
        params[i].first /= (double)X.getN();

    // Standard deviation
    for (size_t i = 0; i < X.getN(); ++i)
        for (size_t j = 1; j < X.getM(); ++j)
            params[j].second += (X[i][j] - params[j].first) * (X[i][j] - params[j].first);
    for (size_t i = 0; i < params.size(); ++i)
        params[i].second = sqrt(params[i].second / ((double)X.getN() - 1));
    
    return params;
}

void normalize(Matrix<double> &X, std::vector<std::pair<double, double>> &params) {
    for (size_t i = 0; i < X.getN(); ++i)
        for (size_t j = 1; j < X.getM(); ++j)
            X[i][j] = (X[i][j] - params[j].first) / params[j].second;
}

std::vector<std::pair<double, double>> standardizationParams(const Matrix<double> &X) {
    std::vector<std::pair<double, double>> params(X.getM(), {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()});
    for (size_t i = 0; i < X.getN(); ++i) {
        for (size_t j = 1; j < X.getM(); ++j) {
            params[j].first = std::min(params[j].first, X[i][j]);
            params[j].second = std::max(params[j].second, X[i][j]);
        }
    }
    return params;
}

void standardize(Matrix<double> &X, std::vector<std::pair<double, double>> &params) {
    for (size_t i = 0; i < X.getN(); ++i)
        for (size_t j = 1; j < X.getM(); ++j)
            X[i][j] = (X[i][j] - params[j].first) / (params[j].second - params[j].first);
}