#ifndef COLLECTION_FACTORY_H
#define COLLECTION_FACTORY_H

#include "../model/MusicDirectory.h"
#include "../model/Tracklist.h"
#include "../model/TracklistSink.h"
#include "../model/Cursor.h"
#include "../model/ShuffleArrangement.h"
#include <memory>
#include <string>

class CollectionFactory {
public:
    static MusicDirectory createDirectory(const std::string& path);
    static Tracklist createTracklist();
    static std::unique_ptr<TracklistSink> createSink(Tracklist& tracklist);
    static std::unique_ptr<Cursor> createCursor(Tracklist& tracklist, ITrackListener& trackBus);
    static ShuffleArrangement createShuffle();
};

#endif //COLLECTION_FACTORY_H