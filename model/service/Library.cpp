#include "Library.h"

Library::Library(MusicLibrary& music_library, Playlist& playlist, PlaybackNotifier& notifier)
    : music_library_(music_library), playlist_(playlist), notifier_(notifier) {}

void Library::insert(const std::string& filePath) const {
    const std::string reason = music_library_.insert(filePath, playlist_);
    if (!reason.empty()) {
        notifier_.onFeedback(reason, false);
        return;
    }
    notifier_.onChanged();
    notifier_.onFeedback("Song added successfully!", true);
}

void Library::remove(const int index) const {
    playlist_.remove(index);
    notifier_.onChanged();
}
