#ifndef COLLECTION_FACTORY_H
#define COLLECTION_FACTORY_H

#include "../library/MusicDirectory.h"
#include "../tracklist/Tracklist.h"
#include "../tracklist/TrackCursor.h"
#include "../tracklist/ShuffleStrategy.h"
#include <memory>
#include <string>

class CollectionFactory {
public:
    static MusicDirectory createMusicDirectory(const std::string& path);
    static Tracklist createTracklist();
    static std::unique_ptr<TrackCursor> createTrackCursor(Tracklist& tracklist, ITrackListener& trackBus);
    static ShuffleStrategy createShuffleStrategy();
};

#endif //COLLECTION_FACTORY_H