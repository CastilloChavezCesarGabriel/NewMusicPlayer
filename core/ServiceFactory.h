#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include "../model/service/Playback.h"
#include "../model/service/Library.h"
#include "../model/service/Setlist.h"
#include "../model/service/Catalog.h"
#include "../model/service/RepeatSwitch.h"
#include <memory>

class ServiceFactory {
public:
    static std::unique_ptr<Playback> createPlayback(Cursor& cursor, Advertisement& ad, RepeatMode& repeat);
    static std::unique_ptr<Library> createLibrary(MusicDirectory& dir, Tracklist& tracklist, ILibraryListener& bus);
    static std::unique_ptr<Setlist> createSetlist(Tracklist& tracklist, Cursor& cursor, ILibraryListener& bus);
    static std::unique_ptr<Catalog> createCatalog(Tracklist& tracklist);
    static std::unique_ptr<RepeatSwitch> createRepeatSwitch(RepeatMode& mode);
};

#endif //SERVICE_FACTORY_H