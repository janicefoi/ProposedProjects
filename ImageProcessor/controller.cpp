#include <iostream>
#include "controller.h"
#include "crop.h"
#include "edge_detection.h"
#include "Grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "MyFilter.h"

std::vector<std::shared_ptr<Filter>> CreateFilters(const std::vector<FilterParsed>& filters_parsed) {
    std::vector<std::shared_ptr<Filter>> filters;
    for (const auto& parsed : filters_parsed) {
        if (parsed.name == "crop" && parsed.args.size() == 2) {
            size_t height = 0;
            size_t width = 0;
            try {
                height = std::stoull(parsed.args[0]);
                width = std::stoull(parsed.args[1]);
            } catch (...) {
                std::cout << "Invalid arguments";
                continue;
            }
            filters.push_back(std::make_shared<Crop>(height, width));
        }
        if (parsed.name == "gs") {
            filters.push_back(std::make_shared<Grayscale>());
        }
        if (parsed.name == "neg") {
            filters.push_back(std::make_shared<Negative>());
        }
        if (parsed.name == "sharp") {
            filters.push_back(std::make_shared<Sharpening>());
        }
        if (parsed.name == "edge" && parsed.args.size() == 1) {
            double threshold = 0.0;
            try {
                threshold = std::stod(parsed.args[0]);
            } catch (...) {
                std::cout << "Invalid argument";
                continue;
            }
            filters.push_back(std::make_shared<EdgeDetection>(threshold));
        }
        if (parsed.name == "mine") {
            filters.push_back(std::make_shared<MyFilter>());
        }
    }
    return filters;
}

Image UseFilters(Image& image, const std::vector<std::shared_ptr<Filter>>& filters) {
    for (const auto& filter : filters) {
        image = filter->Change(image);
    }
    return image;
}