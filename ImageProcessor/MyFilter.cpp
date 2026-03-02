#include "MyFilter.h"

const double PUSHER = 0.6;
const double MAKER = 0.15;
const double EQUAL = 0.3;

Image MyFilter::Change(Image &image) {
    std::vector<std::vector<Color>> colors2(image.colors_.size());
    for (size_t i = 0; i < colors2.size(); ++i) {
        colors2[i].resize(image.colors_[0].size());
    }
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            (colors2[i][j]).Red = image.colors_[i][j].Red * PUSHER + image.colors_[i][j].Green * MAKER;
            (colors2[i][j]).Green = image.colors_[i][j].Green * PUSHER + image.colors_[i][j].Blue * MAKER;
            (colors2[i][j]).Blue =
                image.colors_[i][j].Red * EQUAL + image.colors_[i][j].Green * MAKER + image.colors_[i][j].Blue * PUSHER;
        }
    }
    FilterWithMatrix fm({{-1, -1, -1}, {-1, CHANGER, -1}, {-1, -1, -1}});
    image.colors_ = colors2;
    image = fm.Change(image);
    return image;
}