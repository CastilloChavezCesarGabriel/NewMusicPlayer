#ifndef LIBRARY_H
#define LIBRARY_H

#include "../MusicLibrary.h"
#include "../Playlist.h"
#include "../PlaybackNotifier.h"
#include <string>

class Library {
private:
    MusicLibrary& music_library_;
    Playlist& playlist_;
    PlaybackNotifier& notifier_;

public:
    Library(MusicLibrary& music_library, Playlist& playlist, PlaybackNotifier& notifier);

    void insert(const std::string& filePath) const;
    void remove(int index) const;
};

#endif //LIBRARY_H