#include "CollectionFactory.h"

MusicDirectory CollectionFactory::createDirectory(const std::string& path) {
    return MusicDirectory(path);
}

Tracklist CollectionFactory::createTracklist() {
    return Tracklist();
}

std::unique_ptr<TracklistSink> CollectionFactory::createSink(Tracklist& tracklist) {
    return std::make_unique<TracklistSink>(tracklist);
}

std::unique_ptr<Cursor> CollectionFactory::createCursor(Tracklist& tracklist, ITrackListener& trackBus) {
    return std::make_unique<Cursor>(tracklist, trackBus);
}

ShuffleArrangement CollectionFactory::createShuffle() {
    return ShuffleArrangement();
}