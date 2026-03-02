#include <catch.hpp>
#include "../crop.h"
#include "../Grayscale.h"
#include "../negative.h"
#include "../sharpening.h"
#include "../read_image.h"
#include "../write_image.h"
#include "../edge_detection.h"

double const SMALL_CONST = 0.01;
double const SMALL_CONST_GS = 0.05;
size_t const HEIGHT_FOR_CROP = 500;
size_t const WIDTH_FOR_CROP = 700;
double const THERESOME = 0.5;

TEST_CASE("Read and write") {
    Image image = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\lenna.bmp");
    WriteImage(image, "to_picture.bmp");
    Image image2 =
        ReadImage("C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\cmake-build-debug\\to_picture.bmp");
    bool flag = true;
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            if ((image.colors_[i][j].Red - image2.colors_[i][j].Red) < SMALL_CONST &&
                (image.colors_[i][j].Green - image2.colors_[i][j].Green) < SMALL_CONST &&
                (image.colors_[i][j].Blue - image2.colors_[i][j].Blue) < SMALL_CONST) {
                continue;
            }
            flag = false;
            break;
        }
    }
    REQUIRE(flag == true);
}

TEST_CASE("Crop") {
    Image image = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\lenna.bmp");
    auto crop = std::make_shared<Crop>(HEIGHT_FOR_CROP, WIDTH_FOR_CROP);
    Image image2 = crop->Change(image);
    bool flag = true;
    for (size_t i = 0; i < HEIGHT_FOR_CROP; ++i) {
        for (size_t j = 0; j < WIDTH_FOR_CROP; ++j) {
            if ((image.colors_[i][j].Red - image2.colors_[i][j].Red) < SMALL_CONST &&
                (image.colors_[i][j].Green - image2.colors_[i][j].Green) < SMALL_CONST &&
                (image.colors_[i][j].Blue - image2.colors_[i][j].Blue) < SMALL_CONST) {
                continue;
            }
            flag = false;
            break;
        }
    }
    REQUIRE(flag == true);
}

TEST_CASE("Grayscale") {
    Image image = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\lenna.bmp");
    auto grayscale = std::make_shared<Grayscale>();
    Image image3 = grayscale->Change(image);
    Image image2 = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\lenna_gs_"
        "gs.bmp");
    bool flag = true;
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            if ((image3.colors_[i][j].Red - image2.colors_[i][j].Red) < SMALL_CONST_GS &&
                (image3.colors_[i][j].Green - image2.colors_[i][j].Green) < SMALL_CONST_GS &&
                (image3.colors_[i][j].Blue - image2.colors_[i][j].Blue) < SMALL_CONST_GS) {
                continue;
            }
            flag = false;
            break;
        }
    }
    REQUIRE(flag == true);
}

TEST_CASE("Negative") {
    Image image = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\lenna.bmp");
    auto negative = std::make_shared<Negative>();
    Image image3 = negative->Change(image);
    Image image2 = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\lenna_neg."
        "bmp");
    bool flag = true;
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            if ((image3.colors_[i][j].Red - image2.colors_[i][j].Red) < SMALL_CONST_GS &&
                (image3.colors_[i][j].Green - image2.colors_[i][j].Green) < SMALL_CONST_GS &&
                (image3.colors_[i][j].Blue - image2.colors_[i][j].Blue) < SMALL_CONST_GS) {
                continue;
            }
            flag = false;
            break;
        }
    }
    REQUIRE(flag == true);
}

TEST_CASE("Sharpening") {
    Image image = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\lenna.bmp");
    auto sharpening = std::make_shared<Sharpening>();
    Image image3 = sharpening->Change(image);
    Image image2 = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\lenna_"
        "sharp.bmp");
    bool flag = true;
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            if ((image3.colors_[i][j].Red - image2.colors_[i][j].Red) < SMALL_CONST_GS &&
                (image3.colors_[i][j].Green - image2.colors_[i][j].Green) < SMALL_CONST_GS &&
                (image3.colors_[i][j].Blue - image2.colors_[i][j].Blue) < SMALL_CONST_GS) {
                continue;
            }
            flag = false;
            break;
        }
    }
    REQUIRE(flag == true);
}

TEST_CASE("Edge Detection") {
    Image image = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\flag.bmp");
    auto sharpening = std::make_shared<EdgeDetection>(0.5);
    Image image3 = sharpening->Change(image);
    Image image2 = ReadImage(
        "C:\\Users\\79823\\pmi-223-2-Kirill-Troshkin-kitroshkin\\tasks\\image_processor\\test_script\\data\\flag_edge."
        "bmp");
    bool flag = true;
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            if ((image3.colors_[i][j].Red - image2.colors_[i][j].Red) < SMALL_CONST_GS &&
                (image3.colors_[i][j].Green - image2.colors_[i][j].Green) < SMALL_CONST_GS &&
                (image3.colors_[i][j].Blue - image2.colors_[i][j].Blue) < SMALL_CONST_GS) {
                continue;
            }
            flag = false;
            break;
        }
    }
    REQUIRE(flag == true);
}