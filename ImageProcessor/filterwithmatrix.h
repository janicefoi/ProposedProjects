#pragma once
#include "filter.h"

class FilterWithMatrix : public Filter {
public:
    explicit FilterWithMatrix(std::vector<std::vector<int64_t>> matrix);
    FilterWithMatrix(std::vector<std::vector<int64_t>> matrix, double threshold);
    Image Change(Image& image) override;
    Color TheNearest(const Image& image, int64_t i, int64_t j);

protected:
    std::vector<std::vector<int64_t>> matrix_;
    double threshold_ = 0;
};
