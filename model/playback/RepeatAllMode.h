#ifndef REPEAT_ALL_MODE_H
#define REPEAT_ALL_MODE_H

#include "RepeatStrategy.h"

class RepeatAllMode final : public RepeatStrategy {
public:
    bool apply(TrackCursor& cursor) override;
    RepeatModeKind identify() const override;
};

#endif //REPEAT_ALL_MODE_H