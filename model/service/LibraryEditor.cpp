#include "LibraryEditor.h"
#include "../song/SongFileDeleter.h"
#include "../song/Song.h"
#include <filesystem>

LibraryEditor::LibraryEditor(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& libraryEvents)
    : directory_(directory), tracklist_(tracklist), library_events_(libraryEvents) {}

void LibraryEditor::insert(const std::string& filePath) const {
    if (filePath.empty() || !directory_.accepts(filePath)) {
        library_events_.onFeedback("Unsupported file type.", false);
        return;
    }

    const std::string filename = std::filesystem::path(filePath).filename().string();
    if (directory_.contains(filename)) {
        library_events_.onFeedback("This song already exists.", false);
        return;
    }

    const std::string destination = directory_.copyTo(filePath);
    tracklist_.add(Song(filename, destination));
    library_events_.onChanged();
    library_events_.onFeedback("Song added successfully!", true);
}

void LibraryEditor::remove(const int index) const {
    SongFileDeleter deleter(directory_);
    tracklist_.remove(index, deleter);
    library_events_.onChanged();
}