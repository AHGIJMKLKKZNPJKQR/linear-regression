#include <fstream>
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

void getData(
    Matrix<double> &Xt, std::vector<double> &yt,
    Matrix<double> &Xv, std::vector<double> &yv,
    Matrix<double> &Xs, std::vector<double> &ys
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

    // scale(input);

    srand(SEED);
    std::random_shuffle(input.begin(), input.end());
    
    std::vector<std::vector<double>>::iterator from = input.begin();
    fill(Xt, yt, from, from + (size_t)((double)input.size() * TRAINING_SIZE));
    fill(Xv, yv, from, from + (size_t)((double)input.size() * VALIDATION_SIZE));
    fill(Xs, ys, from, input.end());

    std::vector<std::pair<double, double>> params = normalizationParams(Xt);
    normalize(Xt, params);
    normalize(Xv, params);
    normalize(Xs, params);
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

void applyBase(Matrix<double> &X, const std::function<void(std::vector<double> &)> &transform) {
    for (size_t i = 0; i < X.getN(); ++i)
        transform(X[i]);
}