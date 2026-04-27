#include "Song.h"
#include <algorithm>

Song::Song(const std::string& name, const std::string& path)
       : name_(name), path_(path) {
}

void Song::accept(ISongVisitor& visitor) const {
    visitor.visit(name_, path_);
}

void Song::dispatch(IPathVisitor& visitor) const {
    visitor.visit(path_);
}

bool Song::matches(const std::string& query) const {
    return name_.find(query) != std::string::npos;
}

bool Song::resembles(const std::string& query) const {
    return std::ranges::search(name_, query, [](const char letter, const char target) {
        return std::tolower(static_cast<unsigned char>(letter))
            == std::tolower(static_cast<unsigned char>(target));
    }).begin() != name_.end();
}

bool Song::equals(const Song& other) const {
    return name_ == other.name_ && path_ == other.path_;
}