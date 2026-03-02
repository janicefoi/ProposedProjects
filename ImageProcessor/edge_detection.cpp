#include "edge_detection.h"

Image EdgeDetection::Change(Image& image) {
    Grayscale g;
    image = g.Change(image);
    FilterWithMatrix f({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});
    image = f.Change(image);
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            if (image.colors_[i][j].Red > threshold_) {
                image.colors_[i][j].Red = 1;
                image.colors_[i][j].Green = 1;
                image.colors_[i][j].Blue = 1;
            } else {
                image.colors_[i][j].Red = 0;
                image.colors_[i][j].Green = 0;
                image.colors_[i][j].Blue = 0;
            }
        }
    }
    return image;
}
