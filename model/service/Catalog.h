#ifndef CATALOG_H
#define CATALOG_H

#include "../Tracklist.h"
#include "../ISongVisitor.h"
#include <string>

class Catalog {
private:
    Tracklist& tracklist_;

public:
    explicit Catalog(Tracklist& tracklist);

    void accept(ISongVisitor& visitor) const;
    void search(const std::string& query, ISongVisitor& visitor) const;
};

#endif //CATALOG_H
