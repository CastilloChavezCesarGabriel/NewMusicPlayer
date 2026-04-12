#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include "../service/PlaybackService.h"
#include "../service/LibraryService.h"
#include "../service/Setlist.h"
#include "../service/TrackCatalog.h"
#include "../service/RepeatModeCommand.h"
#include <memory>

class ServiceFactory {
public:
    static std::unique_ptr<PlaybackService> createPlayback(Cursor& cursor, Advertisement& ad, RepeatMode& repeat);
    static std::unique_ptr<LibraryService> createLibrary(MusicDirectory& dir, Tracklist& tracklist, ILibraryListener& bus);
    static std::unique_ptr<Setlist> createSetlist(Tracklist& tracklist, Cursor& cursor, ILibraryListener& bus);
    static std::unique_ptr<TrackCatalog> createTrackCatalog(Tracklist& tracklist);
    static std::unique_ptr<RepeatModeCommand> createRepeatModeCommand(RepeatMode& mode);
};

#endif //SERVICE_FACTORY_H