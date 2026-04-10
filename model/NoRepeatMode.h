#ifndef NO_REPEAT_MODE_H
#define NO_REPEAT_MODE_H

#include "RepeatStrategy.h"

class NoRepeatMode final : public RepeatStrategy {
public:
    bool apply(Cursor& cursor) override;
    RepeatModeKind identify() const override;
};

#endif //NO_REPEAT_MODE_H
