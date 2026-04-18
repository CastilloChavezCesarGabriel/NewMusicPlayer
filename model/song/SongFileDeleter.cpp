#include "SongFileDeleter.h"

SongFileDeleter::SongFileDeleter(MusicDirectory& directory) : directory_(directory) {}

void SongFileDeleter::visit(const std::string& path) {
    directory_.erase(path);
}