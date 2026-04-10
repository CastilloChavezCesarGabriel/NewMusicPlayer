#include "Catalog.h"

Catalog::Catalog(Tracklist& tracklist) : tracklist_(tracklist) {}

void Catalog::accept(ISongVisitor& visitor) const {
    tracklist_.accept(visitor);
}

void Catalog::search(const std::string& query, ISongVisitor& visitor) const {
    tracklist_.search(query, visitor);
}