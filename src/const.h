#pragma once

#include <string>
#include <thread>

const int MAX_ITER = 10;
const double EPS = 1e-5;
const double GRAD_PARAM = 0.95;
const double INIT_GRAD = 0.9;
const double LAMBDA_EPS = 0.2;
const double LAMBDA_JMP = 0.5;
const std::string DATA_PATH = "data/dane.data";
const unsigned int SEED = 3;
const double TRAINING_SIZE = 0.6;
const double VALIDATION_SIZE = 0.2;
const int THREADS = std::thread::hardware_concurrency();
// const int THREADS = 1;