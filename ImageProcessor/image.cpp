#include "image.h"

Image::Image(BitMapHeader bmh, InfoHeader ih, std::vector<std::vector<Color>> colors)
    : bmh_(bmh), ih_(ih), colors_(colors) {
}
