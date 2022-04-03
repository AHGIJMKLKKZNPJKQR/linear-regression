#include <limits>
#include <iostream>
#include <fstream>
#include <thread>

#include "regress.h"
#include "const.h"
#include "utils.h"

void threadFunc(
    const int &lambda_max,
    std::vector<std::vector<double>> &argMin,
    const Matrix<double> &trainingX, const std::vector<double> &trainingY,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &)> &regFunc,
    const int &offset
) {
    for (int i = offset; i < lambda_max; i += THREADS)
        argMin[i] = regFunc(trainingX, trainingY, (double)i * LAMBDA_JMP);
}

std::vector<double> regress(
    const int &lambda_max,
    const Matrix<double> &trainingX, 
    const std::vector<double> &trainingY,
    const Matrix<double> &validationX, 
    const std::vector<double> &validationY,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &)> &regFunc
) {
    std::vector<std::thread> threads;

    std::vector<std::vector<double>> argMin(lambda_max);
    for (int i = 0; i < THREADS; ++i)
        threads.emplace_back(threadFunc, lambda_max, std::ref(argMin), std::cref(trainingX), std::cref(trainingY), regFunc, i);

    for (int i = 0; i < THREADS; ++i)
        threads[i].join();

    int best = 0;
    double dev, mindev = std::numeric_limits<double>::max();
    for (int i = 0; i < lambda_max; ++i)
        if ((dev = fitness(argMin[i], validationX, validationY)) < mindev)
            mindev = dev, best = i;

    return argMin[best];
}

std::vector<double> regress(
    const int &lambda_max,
    const Matrix<double> &trainingX, 
    const std::vector<double> &trainingY,
    const Matrix<double> &validationX, 
    const std::vector<double> &validationY,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &)> &regFunc,
    std::ofstream &dumpFile
) {
    std::vector<std::thread> threads;

    std::vector<std::vector<double>> argMin(lambda_max);
    for (int i = 0; i < THREADS; ++i)
        threads.emplace_back(threadFunc, lambda_max, std::ref(argMin), std::cref(trainingX), std::cref(trainingY), regFunc, i);

    for (int i = 0; i < THREADS; ++i)
        threads[i].join();

    int best = 0;
    double dev, mindev = std::numeric_limits<double>::max();
    for (int i = 0; i < lambda_max; ++i) {
        dumpFile << (LAMBDA_JMP * (double)i) << '\t' << argMin[i];
        if ((dev = fitness(argMin[i], validationX, validationY)) < mindev)
            mindev = dev, best = i;
        dumpFile << dev / (double)validationY.size() << '\n';
    }

    return argMin[best];
}

void threadFunc2(
    const int &l1_max,
    const int &l2_max,
    std::vector<std::vector<std::vector<double>>> &argMin,
    const Matrix<double> &trainingX, const std::vector<double> &trainingY,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &, const double &)> &regFunc,
    const int &offset
) {
    for (int i = offset; i < l1_max; i += THREADS)
        for (int j = 0; j < l2_max; ++j)
            argMin[i][j] = regFunc(trainingX, trainingY, (double)i * LAMBDA_JMP, (double)j * LAMBDA_JMP);
}

std::vector<double> regress(
    const int &l1_max,
    const int &l2_max,
    const Matrix<double> &trainingX, 
    const std::vector<double> &trainingY,
    const Matrix<double> &validationX, 
    const std::vector<double> &validationY,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &, const double &)> &regFunc
) {
    std::vector<std::thread> threads;

    std::vector<std::vector<std::vector<double>>> argMin(l1_max, std::vector<std::vector<double>>(l2_max));
    for (int i = 0; i < THREADS; ++i)
        threads.emplace_back(threadFunc2, l1_max, l2_max, std::ref(argMin), std::cref(trainingX), std::cref(trainingY), regFunc, i);

    for (int i = 0; i < THREADS; ++i)
        threads[i].join();

    std::pair<int, int> best = {0, 0};
    double dev, mindev = std::numeric_limits<double>::max();
    for (int i = 0; i < l1_max; ++i)
        for (int j = 0; j < l2_max; ++j)
            if ((dev = fitness(argMin[i][j], validationX, validationY)) < mindev)
                mindev = dev, best = {i, j};

    return argMin[best.first][best.second];
}

std::vector<double> regress(
    const int &l1_max,
    const int &l2_max,
    const Matrix<double> &trainingX, 
    const std::vector<double> &trainingY,
    const Matrix<double> &validationX, 
    const std::vector<double> &validationY,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &, const double &)> &regFunc,
    std::ofstream &dumpFile
) {
    std::vector<std::thread> threads;

    std::vector<std::vector<std::vector<double>>> argMin(l1_max, std::vector<std::vector<double>>(l2_max));
    for (int i = 0; i < THREADS; ++i)
        threads.emplace_back(threadFunc2, l1_max, l2_max, std::ref(argMin), std::cref(trainingX), std::cref(trainingY), regFunc, i);

    for (int i = 0; i < THREADS; ++i)
        threads[i].join();

    std::pair<int, int> best = {0, 0};
    double dev, mindev = std::numeric_limits<double>::max();
    for (int i = 0; i < l1_max; ++i) {
        for (int j = 0; j < l2_max; ++j) {
            dumpFile << (LAMBDA_JMP * (double)i) << '\t' << (LAMBDA_JMP * (double)j) << '\t' << argMin[i][j];
            if ((dev = fitness(argMin[i][j], validationX, validationY)) < mindev)
                mindev = dev, best = {i, j};
            dumpFile << dev / (double)validationY.size() << '\n';
        }
    }

    return argMin[best.first][best.second];
}

double fitness(const std::vector<double> &theta, const Matrix<double> &X, const std::vector<double> &y) {
    return norm2(X * theta - y);
}
