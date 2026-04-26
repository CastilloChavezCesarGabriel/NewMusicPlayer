#ifndef SONG_TITLE_PARSER_H
#define SONG_TITLE_PARSER_H

#include <string>

class SongTitleParser final {
public:
    static std::string parse(const std::string& name);

private:
    static std::string trim(const std::string& string);
};

#endif //SONG_TITLE_PARSER_H