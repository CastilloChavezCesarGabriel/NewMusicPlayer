#include "Song.h"

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

bool Song::equals(const Song& other) const {
    return name_ == other.name_ && path_ == other.path_;
}