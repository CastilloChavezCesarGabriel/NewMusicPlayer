#include "CollectionFactory.h"

MusicDirectory CollectionFactory::createMusicDirectory(const std::string& path) {
    return MusicDirectory(path);
}

Tracklist CollectionFactory::createTracklist() {
    return Tracklist();
}

std::unique_ptr<TrackCursor> CollectionFactory::createTrackCursor(Tracklist& tracklist, ITrackListener& trackBus) {
    return std::make_unique<TrackCursor>(tracklist, trackBus);
}

ShuffleStrategy CollectionFactory::createShuffleStrategy() {
    return ShuffleStrategy();
}