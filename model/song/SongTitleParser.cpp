#include "SongTitleParser.h"
#include <regex>

std::string SongTitleParser::parse(const std::string& name) {
    static const std::regex pattern(R"(\(\d+\)\s(.+))");
    std::smatch match;
    if (std::regex_match(name, match, pattern)) {
        return trim(match[1]);
    }
    return trim(name);
}

std::string SongTitleParser::trim(const std::string& string) {
    const size_t first = string.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    const size_t last = string.find_last_not_of(" \t\n\r");
    return string.substr(first, last - first + 1);
}