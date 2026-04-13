#ifndef REPEAT_MODE_H
#define REPEAT_MODE_H

#include "RepeatStrategy.h"
#include "../tracklist/TrackCursor.h"
#include "RepeatCoordinator.h"
#include <vector>
#include <memory>

class RepeatMode {
private:
    TrackCursor& cursor_;
    RepeatCoordinator& listener_;
    std::vector<std::unique_ptr<RepeatStrategy>> modes_;
    int mode_index_ = 0;

public:
    RepeatMode(TrackCursor& cursor, RepeatCoordinator& listener);
    void advance();
    bool apply() const;
    void stop() const;
};

#endif //REPEAT_MODE_H