#ifndef REPEAT_STRATEGY_H
#define REPEAT_STRATEGY_H

#include "Cursor.h"
#include "IRepeatListener.h"
#include "RepeatModeKind.h"

class RepeatStrategy {
public:
    virtual ~RepeatStrategy() = default;
    virtual bool apply(Cursor& cursor) = 0;
    virtual RepeatModeKind identify() const = 0;
    void announce(IRepeatListener& listener) const;
};

#endif //REPEAT_STRATEGY_H