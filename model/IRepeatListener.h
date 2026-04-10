#ifndef I_REPEAT_LISTENER_H
#define I_REPEAT_LISTENER_H

#include "RepeatModeKind.h"

class IRepeatListener {
public:
    virtual ~IRepeatListener() = default;
    virtual void onRepeatChanged(RepeatModeKind kind) = 0;
};

#endif //I_REPEAT_LISTENER_H