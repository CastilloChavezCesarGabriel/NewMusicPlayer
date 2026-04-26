#include "MusicDirectory.h"
#include <filesystem>

MusicDirectory::MusicDirectory(const std::string& path) : path_(path) {}

void MusicDirectory::load(ISongVisitor& visitor) const {
    for (const std::string& full : scan()) {
        const std::string filename = std::filesystem::path(full).filename().string();
        visitor.visit(filename, full);
    }
}

bool MusicDirectory::contains(const std::string& filename) const {
    const std::filesystem::path destination = std::filesystem::path(path_) / filename;
    return std::filesystem::exists(destination);
}

void MusicDirectory::erase(const std::string& path) {
    std::filesystem::remove(path);
}

std::string MusicDirectory::copyTo(const std::string& sourcePath) const {
    const std::filesystem::path source(sourcePath);
    const std::string filename = source.filename().string();
    const std::filesystem::path destination = std::filesystem::path(path_) / filename;
    if (!std::filesystem::exists(destination)) {
        std::filesystem::copy_file(source, destination);
    }
    return destination.string();
}

bool MusicDirectory::accepts(const std::string& filename) const {
    return formats_.supports(filename);
}

std::vector<std::string> MusicDirectory::scan() const {
    std::vector<std::string> result;
    if (!std::filesystem::exists(path_)) return result;
    for (const auto& entry : std::filesystem::directory_iterator(path_)) {
        if (entry.is_regular_file() && formats_.supports(entry.path().string())) {
            result.push_back(entry.path().string());
        }
    }
    return result;
}