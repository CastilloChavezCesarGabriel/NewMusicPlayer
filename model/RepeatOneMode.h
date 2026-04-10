#ifndef REPEAT_ONE_MODE_H
#define REPEAT_ONE_MODE_H

#include "RepeatStrategy.h"

class RepeatOneMode final : public RepeatStrategy {
public:
    bool apply(Cursor& cursor) override;
    RepeatModeKind identify() const override;
};

#endif //REPEAT_ONE_MODE_H
