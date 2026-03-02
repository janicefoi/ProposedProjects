#pragma once

#include "filterwithmatrix.h"

const int64_t MIDDLE = 5;

class Sharpening : public FilterWithMatrix {
public:
    Sharpening() : FilterWithMatrix({{0, -1, 0}, {-1, MIDDLE, -1}, {0, -1, 0}}) {
    }
};
