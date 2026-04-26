#ifndef REPEAT_POLICY_H
#define REPEAT_POLICY_H

#include "RepeatStrategy.h"
#include "../tracklist/TrackCursor.h"
#include "RepeatBroadcaster.h"
#include <vector>
#include <memory>

class RepeatPolicy {
private:
    TrackCursor& cursor_;
    RepeatBroadcaster& listener_;
    std::vector<std::unique_ptr<RepeatStrategy>> modes_;
    int mode_index_ = 0;

public:
    RepeatPolicy(TrackCursor& cursor, RepeatBroadcaster& listener);
    void add(std::unique_ptr<RepeatStrategy> strategy);
    void advance();
    bool apply() const;
    void stop() const;
};

#endif //REPEAT_POLICY_H