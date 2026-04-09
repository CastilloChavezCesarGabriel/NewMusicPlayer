#include "Catalog.h"

Catalog::Catalog(Playlist& playlist) : playlist_(playlist) {}

void Catalog::accept(IPlaylistVisitor& visitor) const {
    playlist_.accept(visitor);
}

void Catalog::search(const std::string& query, IPlaylistVisitor& visitor) const {
    playlist_.search(query, visitor);
}