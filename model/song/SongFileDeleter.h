#ifndef SONG_FILE_DELETER_H
#define SONG_FILE_DELETER_H

#include "IPathVisitor.h"
#include "../library/MusicDirectory.h"

class SongFileDeleter final : public IPathVisitor {
private:
    MusicDirectory& directory_;

public:
    explicit SongFileDeleter(MusicDirectory& directory);
    void visit(const std::string& path) override;
};

#endif //SONG_FILE_DELETER_H