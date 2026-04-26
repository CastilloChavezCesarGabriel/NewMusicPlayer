#include "NoRepeatStrategy.h"

bool NoRepeatStrategy::apply(TrackCursor& cursor) {
    if (!cursor.hasNext()) return false;
    cursor.advance();
    return true;
}

RepeatModeKind NoRepeatStrategy::identify() const {
    return RepeatModeKind::None;
}