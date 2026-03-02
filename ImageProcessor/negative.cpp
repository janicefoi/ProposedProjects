#include "negative.h"

Image Negative::Change(Image &image) {
    std::vector<std::vector<Color>> colors2(image.colors_.size());
    for (size_t i = 0; i < colors2.size(); ++i) {
        colors2[i].resize(image.colors_[0].size());
    }
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            (colors2[i][j]).Red = 1 - (image.colors_[i][j]).Red;
            (colors2[i][j]).Green = 1 - (image.colors_[i][j]).Green;
            (colors2[i][j]).Blue = 1 - (image.colors_[i][j]).Blue;
        }
    }
    image.colors_ = colors2;
    return image;
}