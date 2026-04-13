#include "LibraryService.h"
#include "../song/FileEraser.h"
#include "../song/Song.h"
#include <filesystem>

LibraryService::LibraryService(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& library_events)
    : directory_(directory), tracklist_(tracklist), library_events_(library_events) {}

void LibraryService::insert(const std::string& filePath) const {
    if (filePath.empty() || !directory_.accepts(filePath)) {
        library_events_.onFeedback("Unsupported file type.", false);
        return;
    }

    const std::string filename = std::filesystem::path(filePath).filename().string();
    if (directory_.contains(filename)) {
        library_events_.onFeedback("This song already exists.", false);
        return;
    }

    const std::string destination = directory_.store(filePath);
    tracklist_.add(Song(filename, destination));
    library_events_.onChanged();
    library_events_.onFeedback("Song added successfully!", true);
}

void LibraryService::remove(const int index) const {
    FileEraser eraser(directory_);
    tracklist_.discard(index, eraser);
    library_events_.onChanged();
}