#include "write_image.h"
#include <limits>

#include <fstream>

void WriteImage(Image &img, const std::string &file_path) {
    std::ofstream bmpout(file_path, std::ios::binary);
    bmpout.write(reinterpret_cast<char *>(&img.bmh_), sizeof(BitMapHeader));
    bmpout.write(reinterpret_cast<char *>(&img.ih_), sizeof(InfoHeader));

    for (uint32_t i = 0; i < img.ih_.height; ++i) {
        for (uint32_t j = 0; j < img.ih_.width; ++j) {
            RGB current;
            current.Red =
                static_cast<uint8_t>(img.colors_[img.ih_.height - 1 - i][j].Red * std::numeric_limits<uint8_t>::max());
            current.Green = static_cast<uint8_t>(img.colors_[img.ih_.height - 1 - i][j].Green *
                                                 std::numeric_limits<uint8_t>::max());
            current.Blue =
                static_cast<uint8_t>(img.colors_[img.ih_.height - 1 - i][j].Blue * std::numeric_limits<uint8_t>::max());
            bmpout.write(reinterpret_cast<char *>(&current), sizeof(RGB));
        }
        uint32_t to_write = ((3 * img.ih_.width + 3) / 4) * 4 - 3 * img.ih_.width;
        for (uint32_t k = 0; k < to_write; ++k) {
            bmpout.write("\0", 1);
        }
    }
}
