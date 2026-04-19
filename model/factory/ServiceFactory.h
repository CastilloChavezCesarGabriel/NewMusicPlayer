#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include "../service/PlaybackService.h"
#include "../service/LibraryService.h"
#include "../service/Setlist.h"
#include "../service/TrackCatalog.h"
#include <memory>

class ServiceFactory {
public:
    static std::unique_ptr<PlaybackService> createPlayback(TrackCursor& cursor, Advertisement& advertisement, RepeatMode& repeatMode);
    static std::unique_ptr<LibraryService> createLibrary(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& libraryEvents);
    static std::unique_ptr<Setlist> createSetlist(Tracklist& tracklist, TrackCursor& cursor, ILibraryListener& libraryEvents);
    static std::unique_ptr<TrackCatalog> createTrackCatalog(Tracklist& tracklist);
};

#endif //SERVICE_FACTORY_H