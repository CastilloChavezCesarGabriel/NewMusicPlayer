#ifndef PLAYBACK_TRANSPORT_H
#define PLAYBACK_TRANSPORT_H

#include "../tracklist/TrackCursor.h"
#include "../playback/AdScheduler.h"
#include "../playback/RepeatPolicy.h"
#include <string>

class PlaybackTransport {
private:
    TrackCursor& cursor_;
    AdScheduler& advertisement_;
    RepeatPolicy& repeat_mode_;

    void start() const;

public:
    PlaybackTransport(TrackCursor& cursor, AdScheduler& advertisement, RepeatPolicy& repeatMode);

    void play(int index) const;
    void pick(const std::string& name) const;
    void advance() const;
    void retreat() const;
    void end() const;
    void skip() const;
};

#endif //PLAYBACK_TRANSPORT_H