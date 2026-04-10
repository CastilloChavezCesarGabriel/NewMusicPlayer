#ifndef TRACKLIST_SINK_H
#define TRACKLIST_SINK_H

#include "ISongVisitor.h"
#include "Tracklist.h"

class TracklistSink final : public ISongVisitor {
private:
    Tracklist& tracklist_;

public:
    explicit TracklistSink(Tracklist& tracklist);
    void visit(const std::string& name, const std::string& path) override;
};

#endif //TRACKLIST_SINK_H