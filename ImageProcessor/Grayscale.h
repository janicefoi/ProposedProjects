#pragma once
#include "filter.h"

class Grayscale : public Filter {
public:
    Grayscale() = default;
    Image Change(Image& image) override;
};
