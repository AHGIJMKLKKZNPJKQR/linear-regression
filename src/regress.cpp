#include "regress.h"
#include "const.h"
#include "utils.h"
#include <limits>
#include <iostream>
#include <thread>

void threadFunc(
    std::vector<double> &argMin, double &minDev, double &bestL, 
    const Matrix<double> &trainingX, const std::vector<double> &trainingY, 
    const Matrix<double> &validationX, const std::vector<double> &validationY,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &)> &regFunc,
    const int &offset
) {
        std::vector<double> theta(regFunc(trainingX, trainingY, 0));
        double initNorm = norm2(theta);
        double dev = fitness(theta, validationX, validationY);
        argMin = theta;
        minDev = dev;

        for (double lambda = LAMBDA_JMP * (double)offset; norm2(theta) > LAMBDA_EPS * initNorm; lambda += (double)THREADS * LAMBDA_JMP) {
            std::cout << "Lambda = " << lambda << '\n';
            theta = regFunc(trainingX, trainingY, lambda);
            dev = fitness(theta, validationX, validationY);
            if (dev < minDev) {
                minDev = dev;
                argMin = theta;
                bestL = lambda;
            }
        }
    }

std::vector<double> regress(
    const Matrix<double> &trainingX, 
    const std::vector<double> &trainingY,
    const Matrix<double> &validationX, 
    const std::vector<double> &validationY,
    const std::function<std::vector<double>(const Matrix<double> &, const std::vector<double> &, const double &)> &regFunc
) {
    // std::cout << "NUM_THREADS = " << THREADS << '\n';

    std::vector<std::thread> threads;

    std::vector<std::vector<double>> argMin(THREADS);
    std::vector<double> minDev(THREADS);
    std::vector<double> bestL(THREADS, 0);

    for (int i = 0; i < THREADS; ++i)
        threads.emplace_back(
            threadFunc, 
            std::ref(argMin[i]), std::ref(minDev[i]), std::ref(bestL[i]), 
            std::cref(trainingX), std::cref(trainingY), 
            std::cref(validationX), std::cref(validationY),
            regFunc,
            i+1
        );

    for (int i = 0; i < THREADS; ++i)
        threads[i].join();

    int best = 0;
    for (int i = 1; i < THREADS; ++i)
        if (minDev[i] < minDev[best])
            best = i;

    std::cout << "Choosing lambda = " << bestL[best] << '\n';
    return argMin[best];
}

double fitness(const std::vector<double> &theta, const Matrix<double> &X, const std::vector<double> &y) {
    return norm2(X * theta - y);
}