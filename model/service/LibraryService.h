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

public:
    LibraryService(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& libraryEvents);

    void insert(const std::string& filePath) const;
    void remove(int index) const;
};

#endif //LIBRARY_SERVICE_H