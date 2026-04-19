#ifndef SONG_TITLE_H
#define SONG_TITLE_H

#include <string>

class SongTitle final {
public:
    static std::string parse(const std::string& name);

private:
    static std::string trim(const std::string& string);
};

#endif //SONG_TITLE_H