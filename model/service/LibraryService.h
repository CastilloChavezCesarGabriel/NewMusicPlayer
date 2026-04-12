#ifndef LIBRARY_SERVICE_H
#define LIBRARY_SERVICE_H

#include "../library/MusicDirectory.h"
#include "../tracklist/Tracklist.h"
#include "../event/ILibraryListener.h"
#include <string>

class LibraryService {
private:
    MusicDirectory& directory_;
    Tracklist& tracklist_;
    ILibraryListener& library_events_;
    static constexpr auto UNSUPPORTED = "Unsupported file type.";
    static constexpr auto DUPLICATE = "This song already exists.";
    static constexpr auto ADDED = "Song added successfully!";

public:
    LibraryService(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& library_events);

    void insert(const std::string& filePath) const;
    void remove(int index) const;
};

#endif //LIBRARY_SERVICE_H