#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iomanip>

#include "const.h"
#include "utils.h"
#include "ridge.h"
#include "lasso.h"
#include "regress.h"
#include "parse.h"
#include "output.h"
#include "base.h"
#include "meta.h"
#include "main.h"
#include "elastic.h"

void doTrainingWithDump(
    const Matrix<double> &Xt, const std::vector<double> &yt,
    const Matrix<double> &Xv, const std::vector<double> &yv,
    const baseChange &change
) {
    std::cout << "DUMPING DATA...\n";
    std::cout << "RIDGE REGRESSION: ";
    std::ofstream ridgeFile;
    ridgeFile.open(RIDGE_DUMP + "." + change.name);
    ridgeFile << std::fixed << std::setprecision(4);
    std::cout << "DONE\n";
    
    std::vector<double> theta = regress(RIDGE_LAMBDA_MAX, Xt, yt, Xv, yv, ridgeRegression, ridgeFile);
    ridgeFile.close();
    saveParamsToFile(theta, RIDGE_SOLUTION + "." + change.name);
    
    std::cout << "LASSO REGRESSION: ";
    std::ofstream lassoFile;
    lassoFile.open(LASSO_DUMP + "." + change.name);
    lassoFile << std::fixed << std::setprecision(4);
    std::cout << "DONE\n";

    theta = regress(LASSO_LAMBDA_MAX, Xt, yt, Xv, yv, lassoRegression, lassoFile);
    lassoFile.close();
    saveParamsToFile(theta, LASSO_SOLUTION + "." + change.name);
    
    std::cout << "ELASTIC NET REGRESSION: ";
    std::ofstream elasticFile;
    elasticFile.open(ELASTIC_DUMP + "." + change.name);
    elasticFile << std::fixed << std::setprecision(4);
    std::cout << "DONE\n";

    theta = regress(LASSO_LAMBDA_MAX, RIDGE_LAMBDA_MAX, Xt, yt, Xv, yv, elasticNetRegression, elasticFile);
    elasticFile.close();
    saveParamsToFile(theta, ELASTIC_SOLUTION + "." + change.name);

    std::cout << "\n";
}

void doTraining(
    const Matrix<double> &Xt, const std::vector<double> &yt,
    Matrix<double> &Xta, std::vector<double> &yta,
    const Matrix<double> &Xv, const std::vector<double> &yv,
    const Matrix<double> &Xs, const std::vector<double> &ys,
    std::vector<double> &ridgeAvgErr,
    std::vector<double> &lassoAvgErr,
    std::vector<double> &elasticAvgErr,
    const int &trainingSize
) {
    std::cout << "TRAINING SIZE FRACTION = " << TRAINING_FRACS[trainingSize] << '\n';

    while ((double)Xta.getN() < (double)Xt.getN() * TRAINING_FRACS[trainingSize]) {
        Xta.addRow(Xt[Xta.getN()]);
        yta.push_back(yt[yta.size()]);
    }

    std::cout << "RIDGE REGRESSION: ";
    std::vector<double> theta = regress(RIDGE_LAMBDA_MAX, Xta, yta, Xv, yv, ridgeRegression);    
    ridgeAvgErr[trainingSize] += fitness(theta, Xs, ys) / (double)ys.size();
    std::cout << "DONE\n";

    std::cout << "LASSO REGRESSION: ";
    theta = regress(LASSO_LAMBDA_MAX, Xta, yta, Xv, yv, lassoRegression);
    lassoAvgErr[trainingSize] += fitness(theta, Xs, ys) / (double)ys.size();

    std::cout << "DONE\n";

    std::cout << "ELASTIC NET REGRESSION: ";
    theta = regress(LASSO_LAMBDA_MAX, RIDGE_LAMBDA_MAX, Xta, yta, Xv, yv, elasticNetRegression);
    elasticAvgErr[trainingSize] += fitness(theta, Xs, ys) / (double)ys.size();
    std::cout << "DONE\n";

    std::cout << "\n";
}


void doRegression() {
    for (const baseChange & change: changes) {
        std::cout << "BASE FUNCTION: " << change.name << '\n';

        std::vector<double> ridgeAvgErr(TRAINING_FRACS.size(), 0);
        std::vector<double> lassoAvgErr(TRAINING_FRACS.size(), 0);
        std::vector<double> elasticAvgErr(TRAINING_FRACS.size(), 0);
        for (int seed = 0; seed < NUMBER_OF_RUNS; ++seed) { 
            std::cout << "SEED = " << seed << '\n';
            
            Matrix<double> Xt, Xv, Xs, Xta;
            std::vector<double> yt, yv, ys, yta;    
            getData(Xt, yt, Xv, yv, Xs, ys, seed);
            Xt = applyBase(Xt, change.func);
            Xv = applyBase(Xv, change.func);
            Xs = applyBase(Xs, change.func);
            
            for (int trainingSize = 0; trainingSize < (int)TRAINING_FRACS.size(); ++trainingSize)
                doTraining(Xt, yt, Xta, yta, Xv, yv, Xs, ys, ridgeAvgErr, lassoAvgErr, elasticAvgErr, trainingSize);
            doTrainingWithDump(Xt, yt, Xv, yv, change);   
        }

        for (double &i : ridgeAvgErr)
            i /= NUMBER_OF_RUNS;

        for (double &i : lassoAvgErr)
            i /= NUMBER_OF_RUNS;

        for (double &i : elasticAvgErr)
            i /= NUMBER_OF_RUNS;

        std::ofstream errFile;
        errFile.open(RIDGE_ERROR + "." + change.name);
        for (int i = 0; i < (int)ridgeAvgErr.size(); ++i)
            errFile << TRAINING_FRACS[i] << '\t' << ridgeAvgErr[i] << '\n';
        errFile.close();

        errFile.open(LASSO_ERROR + "." + change.name);
        for (int i = 0; i < (int)lassoAvgErr.size(); ++i)
            errFile << TRAINING_FRACS[i] << '\t' << lassoAvgErr[i] << '\n';
        errFile.close();
        
        errFile.open(ELASTIC_ERROR + "." + change.name);
        for (int i = 0; i < (int)elasticAvgErr.size(); ++i)
            errFile << TRAINING_FRACS[i] << '\t' << elasticAvgErr[i] << '\n';
        errFile.close();
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(4);

    // std::pair<double, double> meta1 = calcMeta(1), meta2 = calcMeta(6);
    // changes.push_back({ base::metaSin(meta1.first, meta1.second, 1), "obs1" });
    // changes.push_back({ base::metaSin(meta2.first, meta2.second, 6), "obs6" });
    // std::vector<std::function<double(const double &)>> funcs {
    //     [=](const double &x) -> double { return ::sin(meta1.second * (x - meta1.first)); },
    //     [](const double &x) -> double { return x; },
    //     [](const double &x) -> double { return x; },
    //     [](const double &x) -> double { return x; },
    //     [](const double &x) -> double { return x; },
    //     [=](const double &x) -> double { return ::sin(meta2.second * (x - meta2.first)); }
    // };
    // changes.push_back({ base::generic(funcs), "obs16" });
    doRegression();
}