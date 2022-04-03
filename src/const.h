#pragma once

#include <string>
#include <vector>
#include <thread>

const int MAX_ITER = 100;
const double EPS = 1e-5;
const double GRAD_PARAM = 0.95;
const double INIT_GRAD = 0.9;
const int RIDGE_LAMBDA_MAX = 3000;
const int LASSO_LAMBDA_MAX = 5000;
const double LAMBDA_JMP = 5;

const std::string DATA_PATH = "data/dane.data";
const unsigned int SEED = 2;
const double TRAINING_SIZE = 0.6;
const double VALIDATION_SIZE = 0.2;

const std::string NORMALIZED_DATA_FILE = "data/norm.data"; 

const std::string RIDGE_DUMP = "out/ridge.dump"; 
const std::string RIDGE_ERROR = "out/ridge.err"; 
const std::string RIDGE_SOLUTION = "out/ridge.sol"; 

const std::string LASSO_DUMP = "out/lasso.dump"; 
const std::string LASSO_ERROR = "out/lasso.err"; 
const std::string LASSO_SOLUTION = "out/lasso.sol";

const std::string ELASTIC_DUMP = "out/elastic.dump"; 
const std::string ELASTIC_ERROR = "out/elastic.err"; 
const std::string ELASTIC_SOLUTION = "out/elastic.sol";

const std::string SINE_META = "out/sine.dump.meta";
const double MAX_SCALE = 4;
const double MIN_SCALE = 2;

const int NUMBER_OF_RUNS = 4;
const std::vector<double> TRAINING_FRACS {
    0.01, 0.02, 0.03, 0.05, 0.1, 0.125, 0.2, 0.25, 0.375, 0.5, 0.625, 0.75, 1
};

const int THREADS = std::thread::hardware_concurrency();
// const int THREADS = 1;