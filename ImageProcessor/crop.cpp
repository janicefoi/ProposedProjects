#include "crop.h"

Crop::Crop(size_t height, size_t width) : heightc_(height), widthc_(width) {
}

Image Crop::Change(Image& image) {
    if (heightc_ < image.colors_.size()) {
        image.colors_.resize(heightc_);
        image.ih_.height = heightc_;
    }
    if (widthc_ < image.colors_[0].size()) {
        for (auto vec : image.colors_) {
            vec.resize(widthc_);
        }
        image.ih_.width = widthc_;
    }
    return image;
}