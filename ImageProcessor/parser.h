#pragma once
#include <string>
#include <vector>

struct FilterParsed {
    std::string name;
    std::vector<std::string> args;
};

struct ParserWords {
    std::string input;
    std::string output;
    std::vector<FilterParsed> filters;
};

ParserWords Parse(int argc, char** argv);