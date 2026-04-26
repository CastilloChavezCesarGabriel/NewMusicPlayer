#ifndef LIBRARY_EDITOR_H
#define LIBRARY_EDITOR_H

#include "../library/MusicDirectory.h"
#include "../tracklist/Tracklist.h"
#include "../event/ILibraryListener.h"
#include <string>

class LibraryEditor {
private:
    MusicDirectory& directory_;
    Tracklist& tracklist_;
    ILibraryListener& library_events_;

public:
    LibraryEditor(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& libraryEvents);

    void insert(const std::string& filePath) const;
    void remove(int index) const;
};

#endif //LIBRARY_EDITOR_H