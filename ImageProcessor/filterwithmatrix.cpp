#include "filterwithmatrix.h"

FilterWithMatrix::FilterWithMatrix(std::vector<std::vector<int64_t>> matrix) : matrix_(matrix) {
}
FilterWithMatrix::FilterWithMatrix(std::vector<std::vector<int64_t>> matrix, double threshold)
    : matrix_(matrix), threshold_(threshold) {
}

Color FilterWithMatrix::TheNearest(const Image& image, int64_t j, int64_t i) {
    if (i < 0) {
        if (j < 0) {
            return image.colors_[0][0];
        }
        if (j >= static_cast<int64_t>(image.colors_.size())) {
            return image.colors_[image.colors_.size() - 1][0];
        }
        return image.colors_[j][0];
    }
    if (i >= static_cast<int64_t>(image.colors_[0].size())) {
        if (j < 0) {
            return image.colors_[0][image.colors_[0].size() - 1];
        }
        if (j >= static_cast<int64_t>(image.colors_.size())) {
            return image.colors_[image.colors_.size() - 1][image.colors_[0].size() - 1];
        }
        return image.colors_[j][image.colors_[0].size() - 1];
    }
    if (j < 0) {
        return image.colors_[0][i];
    }
    if (j >= static_cast<int64_t>(image.colors_.size())) {
        return image.colors_[image.colors_.size() - 1][i];
    }
    return image.colors_[j][i];
}

Image FilterWithMatrix::Change(Image& image) {
    std::vector<std::vector<Color>> colors2(image.colors_.size());
    for (size_t i = 0; i < colors2.size(); ++i) {
        colors2[i].resize(image.colors_[0].size());
    }
    for (int64_t x = 0; x < static_cast<int64_t>(image.colors_.size()); ++x) {
        for (int64_t y = 0; y < static_cast<int64_t>(image.colors_[0].size()); ++y) {
            double number_red = 0;
            double number_green = 0;
            double number_blue = 0;
            for (int64_t i = 0; i < static_cast<int64_t>(matrix_.size()); ++i) {
                for (int64_t j = 0; j < static_cast<int64_t>(matrix_[0].size()); ++j) {
                    number_red += static_cast<double>(matrix_[i][j]) *
                                  TheNearest(image, x - static_cast<int64_t>(matrix_.size() - 1) / 2 + i,
                                             y - static_cast<int64_t>(matrix_.size() - 1) / 2 + j)
                                      .Red;
                    number_green += static_cast<double>(matrix_[i][j]) *
                                    TheNearest(image, x - static_cast<int64_t>(matrix_.size() - 1) / 2 + i,
                                               y - static_cast<int64_t>(matrix_.size() - 1) / 2 + j)
                                        .Green;
                    number_blue += static_cast<double>(matrix_[i][j]) *
                                   TheNearest(image, x - static_cast<int64_t>(matrix_.size() - 1) / 2 + i,
                                              y - static_cast<int64_t>(matrix_.size() - 1) / 2 + j)
                                       .Blue;
                }
                colors2[x][y].Red = std::min(static_cast<double>(1), std::max(static_cast<double>(0), number_red));
                colors2[x][y].Green = std::min(static_cast<double>(1), std::max(static_cast<double>(0), number_green));
                colors2[x][y].Blue = std::min(static_cast<double>(1), std::max(static_cast<double>(0), number_blue));
            }
        }
    }
    image.colors_ = colors2;
    return image;
}