#ifndef REPEAT_ONE_STRATEGY_H
#define REPEAT_ONE_STRATEGY_H

#include "RepeatStrategy.h"

class RepeatOneStrategy final : public RepeatStrategy {
public:
    bool apply(TrackCursor& cursor) override;
    RepeatModeKind identify() const override;
};

#endif //REPEAT_ONE_STRATEGY_H