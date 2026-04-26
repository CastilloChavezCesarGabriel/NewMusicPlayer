#ifndef PLAYBACK_SERVICE_H
#define PLAYBACK_SERVICE_H

#include "../tracklist/TrackCursor.h"
#include "../playback/Advertisement.h"
#include "../playback/RepeatPolicy.h"
#include <string>

class PlaybackService {
private:
    TrackCursor& cursor_;
    Advertisement& advertisement_;
    RepeatPolicy& repeat_mode_;

    void start() const;

public:
    PlaybackService(TrackCursor& cursor, Advertisement& advertisement, RepeatPolicy& repeatMode);

    void play(int index) const;
    void pick(const std::string& name) const;
    void advance() const;
    void retreat() const;
    void end() const;
    void skip() const;
};

#endif //PLAYBACK_SERVICE_H