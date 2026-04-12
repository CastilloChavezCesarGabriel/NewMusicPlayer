#include "ServiceFactory.h"

std::unique_ptr<PlaybackService> ServiceFactory::createPlayback(Cursor& cursor, Advertisement& ad, RepeatMode& repeat) {
    return std::make_unique<PlaybackService>(cursor, ad, repeat);
}

std::unique_ptr<LibraryService> ServiceFactory::createLibrary(MusicDirectory& dir, Tracklist& tracklist, ILibraryListener& bus) {
    return std::make_unique<LibraryService>(dir, tracklist, bus);
}

std::unique_ptr<Setlist> ServiceFactory::createSetlist(Tracklist& tracklist, Cursor& cursor, ILibraryListener& bus) {
    return std::make_unique<Setlist>(tracklist, cursor, bus);
}

std::unique_ptr<TrackCatalog> ServiceFactory::createTrackCatalog(Tracklist& tracklist) {
    return std::make_unique<TrackCatalog>(tracklist);
}

std::unique_ptr<RepeatModeCommand> ServiceFactory::createRepeatModeCommand(RepeatMode& mode) {
    return std::make_unique<RepeatModeCommand>(mode);
}