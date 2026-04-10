#include "FileEraser.h"

FileEraser::FileEraser(MusicDirectory& directory) : directory_(directory) {}

void FileEraser::visit(const std::string& path) {
    directory_.erase(path);
}
