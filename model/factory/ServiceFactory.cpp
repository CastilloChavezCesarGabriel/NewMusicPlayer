#include "ServiceFactory.h"

std::unique_ptr<PlaybackTransport> ServiceFactory::createPlayback(TrackCursor& cursor, AdScheduler& adScheduler, RepeatPolicy& repeatPolicy) {
    return std::make_unique<PlaybackTransport>(cursor, adScheduler, repeatPolicy);
}

std::unique_ptr<LibraryEditor> ServiceFactory::createLibrary(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& libraryEvents) {
    return std::make_unique<LibraryEditor>(directory, tracklist, libraryEvents);
}

std::unique_ptr<Setlist> ServiceFactory::createSetlist(Tracklist& tracklist, TrackCursor& cursor, ILibraryListener& libraryEvents) {
    return std::make_unique<Setlist>(tracklist, cursor, libraryEvents);
}

std::unique_ptr<TrackCatalog> ServiceFactory::createTrackCatalog(Tracklist& tracklist) {
    return std::make_unique<TrackCatalog>(tracklist);
}