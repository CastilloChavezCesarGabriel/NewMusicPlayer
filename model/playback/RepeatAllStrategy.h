#ifndef REPEAT_ALL_STRATEGY_H
#define REPEAT_ALL_STRATEGY_H

#include "RepeatStrategy.h"

class RepeatAllStrategy final : public RepeatStrategy {
public:
    bool apply(TrackCursor& cursor) override;
    RepeatModeKind identify() const override;
};

#endif //REPEAT_ALL_STRATEGY_H