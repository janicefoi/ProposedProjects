#pragma once
#include "image.h"

class Filter {
public:
    virtual Image Change(Image& image) = 0;
    virtual ~Filter() = default;
};
