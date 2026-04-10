#include "ServiceFactory.h"

std::unique_ptr<Playback> ServiceFactory::createPlayback(Cursor& cursor, Advertisement& ad, RepeatMode& repeat) {
    return std::make_unique<Playback>(cursor, ad, repeat);
}

std::unique_ptr<Library> ServiceFactory::createLibrary(MusicDirectory& dir, Tracklist& tracklist, ILibraryListener& bus) {
    return std::make_unique<Library>(dir, tracklist, bus);
}

std::unique_ptr<Setlist> ServiceFactory::createSetlist(Tracklist& tracklist, Cursor& cursor, ILibraryListener& bus) {
    return std::make_unique<Setlist>(tracklist, cursor, bus);
}

std::unique_ptr<Catalog> ServiceFactory::createCatalog(Tracklist& tracklist) {
    return std::make_unique<Catalog>(tracklist);
}

std::unique_ptr<RepeatSwitch> ServiceFactory::createRepeatSwitch(RepeatMode& mode) {
    return std::make_unique<RepeatSwitch>(mode);
}
