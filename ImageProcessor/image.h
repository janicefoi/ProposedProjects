#pragma once

#include <vector>
#include "color.h"

#pragma pack(push, 1)
struct BitMapHeader {
    uint16_t type;
    uint32_t size = 0;
    uint16_t unused1 = 0;
    uint16_t unused2 = 0;
    uint32_t offset = 0;
};

struct InfoHeader {
    uint32_t size = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    uint16_t planes = 0;
    uint16_t bit_count = 0;
    uint32_t compression = 0;
    uint32_t size_image = 0;
    uint32_t x_pels = 0;
    uint32_t y_pels = 0;
    uint32_t crl_used = 0;
    uint32_t crl_important = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RGB {
    uint8_t Blue;
    uint8_t Green;
    uint8_t Red;
};
#pragma pack(pop)

class Image {
public:
    BitMapHeader bmh_;
    InfoHeader ih_;
    explicit Image(BitMapHeader bmh, InfoHeader ih, std::vector<std::vector<Color>> colors);
    std::vector<std::vector<Color>> colors_;
};
