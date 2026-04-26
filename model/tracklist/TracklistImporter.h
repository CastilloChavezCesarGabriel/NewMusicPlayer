#ifndef TRACKLIST_IMPORTER_H
#define TRACKLIST_IMPORTER_H

#include "Tracklist.h"
#include "../song/ISongVisitor.h"

class TracklistImporter final : public ISongVisitor {
private:
    Tracklist& tracklist_;

public:
    explicit TracklistImporter(Tracklist& tracklist);
    void visit(const std::string& name, const std::string& path) override;
};

#endif //TRACKLIST_IMPORTER_H
