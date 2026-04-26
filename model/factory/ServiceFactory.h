#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include "../service/PlaybackTransport.h"
#include "../service/LibraryEditor.h"
#include "../service/Setlist.h"
#include "../service/TrackCatalog.h"
#include <memory>

class ServiceFactory {
public:
    static std::unique_ptr<PlaybackTransport> createPlayback(TrackCursor& cursor, AdScheduler& adScheduler, RepeatPolicy& repeatPolicy);
    static std::unique_ptr<LibraryEditor> createLibrary(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& libraryEvents);
    static std::unique_ptr<Setlist> createSetlist(Tracklist& tracklist, TrackCursor& cursor, ILibraryListener& libraryEvents);
    static std::unique_ptr<TrackCatalog> createTrackCatalog(Tracklist& tracklist);
};

#endif //SERVICE_FACTORY_H