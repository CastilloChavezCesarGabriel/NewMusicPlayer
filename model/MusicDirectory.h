#ifndef MUSIC_DIRECTORY_H
#define MUSIC_DIRECTORY_H

#include "ISongVisitor.h"
#include "FormatRegistry.h"
#include <string>
#include <vector>

class MusicDirectory final {
private:
    std::string path_;
    FormatRegistry formats_;

public:
    explicit MusicDirectory(const std::string& path);

    void load(ISongVisitor& visitor) const;
    bool contains(const std::string& filename) const;
    static void erase(const std::string& path);
    std::string store(const std::string& sourcePath) const;
    bool accepts(const std::string& filename) const;
    std::vector<std::string> scan() const;
};

#endif //MUSIC_DIRECTORY_H
