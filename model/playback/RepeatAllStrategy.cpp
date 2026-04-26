#include "RepeatAllStrategy.h"

bool RepeatAllStrategy::apply(TrackCursor& cursor) {
    if (cursor.hasNext()) {
        cursor.advance();
    } else {
        cursor.select(0);
    }
    return true;
}

RepeatModeKind RepeatAllStrategy::identify() const {
    return RepeatModeKind::All;
}