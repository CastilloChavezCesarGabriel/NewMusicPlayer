#ifndef SONG_H
#define SONG_H

#include "ISongVisitor.h"
#include "IPathVisitor.h"
#include <string>

class Song {
private:
    std::string name_;
    std::string path_;

public:
    Song(const std::string& name, const std::string& path);

    void accept(ISongVisitor& visitor) const;
    void stream(IPathVisitor& visitor) const;
    bool matches(const std::string& query) const;
    bool identifies(const Song& other) const;
};

#endif //SONG_H