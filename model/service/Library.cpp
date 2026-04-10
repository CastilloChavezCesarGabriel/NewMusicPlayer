#include "Library.h"
#include "../FileEraser.h"
#include "../Song.h"
#include <filesystem>

Library::Library(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& library_events)
    : directory_(directory), tracklist_(tracklist), library_events_(library_events) {}

void Library::insert(const std::string& filePath) const {
    if (filePath.empty() || !directory_.accepts(filePath)) {
        library_events_.onFeedback(UNSUPPORTED, false);
        return;
    }
    const std::string filename = std::filesystem::path(filePath).filename().string();
    if (directory_.contains(filename)) {
        library_events_.onFeedback(DUPLICATE, false);
        return;
    }
    const std::string destination = directory_.store(filePath);
    tracklist_.add(Song(filename, destination));
    library_events_.onChanged();
    library_events_.onFeedback(ADDED, true);
}

void Library::remove(const int index) const {
    FileEraser eraser(directory_);
    tracklist_.discard(index, eraser);
    library_events_.onChanged();
}