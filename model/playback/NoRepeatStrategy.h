#ifndef NO_REPEAT_STRATEGY_H
#define NO_REPEAT_STRATEGY_H

#include "RepeatStrategy.h"

class NoRepeatStrategy final : public RepeatStrategy {
public:
    bool apply(TrackCursor& cursor) override;
    RepeatModeKind identify() const override;
};

#endif //NO_REPEAT_STRATEGY_H