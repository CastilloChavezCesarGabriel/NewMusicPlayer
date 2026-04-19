#include "TrackCatalog.h"

TrackCatalog::TrackCatalog(Tracklist& tracklist) : tracklist_(tracklist) {}

void TrackCatalog::accept(ISongVisitor& visitor) const {
    tracklist_.accept(visitor);
}

void TrackCatalog::search(const std::string& query, ISongVisitor& visitor) const {
    tracklist_.filter(query, visitor);
}