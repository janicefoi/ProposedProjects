#pragma once
#include "filter.h"

class Crop : public Filter {
public:
    Crop(size_t height, size_t width);
    Image Change(Image& image) override;

private:
    size_t heightc_;
    size_t widthc_;
};