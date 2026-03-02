#pragma once

#include "filterwithmatrix.h"
#include "Grayscale.h"

class EdgeDetection : public FilterWithMatrix {
public:
    explicit EdgeDetection(double threshold) : FilterWithMatrix({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}, threshold) {
    }
    Image Change(Image& image) override;
};
