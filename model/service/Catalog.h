#ifndef CATALOG_H
#define CATALOG_H

#include "../Playlist.h"
#include "../IPlaylistVisitor.h"
#include <string>

class Catalog {
private:
    Playlist& playlist_;

public:
    explicit Catalog(Playlist& playlist);

    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;
};

#endif //CATALOG_H
