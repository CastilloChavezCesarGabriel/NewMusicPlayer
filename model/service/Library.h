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
    static constexpr const char* UNSUPPORTED = "Unsupported file type.";
    static constexpr const char* DUPLICATE = "This song already exists.";
    static constexpr const char* ADDED = "Song added successfully!";

public:
    Library(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& library_events);

    void insert(const std::string& filePath) const;
    void remove(int index) const;
};

#endif //LIBRARY_H
