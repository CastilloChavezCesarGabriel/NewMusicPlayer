#ifndef COLLECTION_FACTORY_H
#define COLLECTION_FACTORY_H

#include "../library/MusicDirectory.h"
#include "../tracklist/Tracklist.h"
#include "../tracklist/Cursor.h"
#include "../tracklist/ShuffleArrangement.h"
#include <memory>
#include <string>

class CollectionFactory {
public:
    static MusicDirectory createDirectory(const std::string& path);
    static Tracklist createTracklist();
    static std::unique_ptr<Cursor> createCursor(Tracklist& tracklist, ITrackListener& trackBus);
    static ShuffleArrangement createShuffle();
};

#endif //COLLECTION_FACTORY_H