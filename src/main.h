#pragma once

#include <vector>
#include "base.h"

std::vector<baseChange> changes {
    { base::pow(1), "basic" },
    { base::pow(2), "square" },
    { base::pow(3), "cube"},
    // { base::pow(5), "pow5"},
    { base::sqrt, "sqrt" },
    { base::sig, "sig"},
    { base::sin, "sin" },
    { base::gauss(1), "gauss1" },
    { base::gauss(2), "gauss2" }
    // { base::gauss(3), "gauss3" },
    // { base::gauss(4), "gauss4" },
};