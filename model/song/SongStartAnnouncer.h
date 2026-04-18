#ifndef SONG_START_ANNOUNCER_H
#define SONG_START_ANNOUNCER_H

#include "IPathVisitor.h"
#include "../event/ITrackListener.h"

class SongStartAnnouncer final : public IPathVisitor {
private:
    ITrackListener& tracks_;

public:
    explicit SongStartAnnouncer(ITrackListener& tracks);
    void visit(const std::string& path) override;
};

#endif //SONG_START_ANNOUNCER_H