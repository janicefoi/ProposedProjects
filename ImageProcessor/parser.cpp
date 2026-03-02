#include "parser.h"

ParserWords Parse(int argc, char** argv) {
    if (argc < 2) {
        throw std::exception();
    }
    ParserWords parser_words;
    parser_words.input = argv[1];
    parser_words.output = argv[2];
    for (int i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            FilterParsed filter;
            filter.name = std::string(argv[i]).substr(1);
            parser_words.filters.emplace_back(filter);
            continue;
        }
        parser_words.filters.back().args.emplace_back(argv[i]);
    }
    return parser_words;
}