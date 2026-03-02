#pragma once
#include "filter.h"

class Negative : public Filter {
public:
    Negative() = default;
    Image Change(Image& image) override;
};
