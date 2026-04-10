#ifndef LIBRARY_H
#define LIBRARY_H

#include "../MusicDirectory.h"
#include "../Tracklist.h"
#include "../ILibraryListener.h"
#include <string>

class Library {
private:
    MusicDirectory& directory_;
    Tracklist& tracklist_;
    ILibraryListener& library_events_;
    static constexpr auto UNSUPPORTED = "Unsupported file type.";
    static constexpr auto DUPLICATE = "This song already exists.";
    static constexpr auto ADDED = "Song added successfully!";

public:
    Library(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& library_events);

    void insert(const std::string& filePath) const;
    void remove(int index) const;
};

#endif //LIBRARY_H