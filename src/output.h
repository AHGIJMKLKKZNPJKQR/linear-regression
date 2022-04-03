#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "utils.h"

template <typename T>
void saveParamsToFile(const std::vector<T> &theta, const std::string &filename) {
    std::ofstream file;
    file.open(filename, std::ofstream::out | std::ofstream::trunc);
    file << theta;
    file.close();
}