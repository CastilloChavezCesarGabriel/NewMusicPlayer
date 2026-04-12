#ifndef TRACK_CATALOG_H
#define TRACK_CATALOG_H

#include "../tracklist/Tracklist.h"
#include "../song/ISongVisitor.h"
#include <string>

class TrackCatalog {
private:
    Tracklist& tracklist_;

public:
    explicit TrackCatalog(Tracklist& tracklist);

    void accept(ISongVisitor& visitor) const;
    void search(const std::string& query, ISongVisitor& visitor) const;
};

#endif //TRACK_CATALOG_H