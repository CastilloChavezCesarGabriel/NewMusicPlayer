#include "ServiceFactory.h"

std::unique_ptr<PlaybackService> ServiceFactory::createPlayback(TrackCursor& cursor, Advertisement& advertisement, RepeatMode& repeatMode) {
    return std::make_unique<PlaybackService>(cursor, advertisement, repeatMode);
}

std::unique_ptr<LibraryService> ServiceFactory::createLibrary(MusicDirectory& directory, Tracklist& tracklist, ILibraryListener& libraryEvents) {
    return std::make_unique<LibraryService>(directory, tracklist, libraryEvents);
}

std::unique_ptr<Setlist> ServiceFactory::createSetlist(Tracklist& tracklist, TrackCursor& cursor, ILibraryListener& libraryEvents) {
    return std::make_unique<Setlist>(tracklist, cursor, libraryEvents);
}

std::unique_ptr<TrackCatalog> ServiceFactory::createTrackCatalog(Tracklist& tracklist) {
    return std::make_unique<TrackCatalog>(tracklist);
}