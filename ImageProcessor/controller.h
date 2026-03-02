#pragma once
#include "filter.h"
#include "parser.h"
#include <memory>

std::vector<std::shared_ptr<Filter>> CreateFilters(const std::vector<FilterParsed>& filter);
Image UseFilters(Image& image, const std::vector<std::shared_ptr<Filter>>& filters);