#ifndef PLAYBACK_TRANSPORT_H
#define PLAYBACK_TRANSPORT_H

#include "../tracklist/TrackCursor.h"
#include "../playback/AdScheduler.h"
#include "../playback/RepeatPolicy.h"
#include <string>

class PlaybackTransport {
private:
    TrackCursor& cursor_;
    AdScheduler& ad_scheduler_;
    RepeatPolicy& repeat_policy_;

    void start() const;
    bool resume() const;

public:
    PlaybackTransport(TrackCursor& cursor, AdScheduler& adScheduler, RepeatPolicy& repeatPolicy);

    void play(int index) const;
    void pick(const std::string& name) const;
    void advance() const;
    void retreat() const;
    void end() const;
    bool skip() const;
};

#endif //PLAYBACK_TRANSPORT_H