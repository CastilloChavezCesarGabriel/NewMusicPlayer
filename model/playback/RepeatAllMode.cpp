#include "RepeatAllMode.h"

bool RepeatAllMode::apply(TrackCursor& cursor) {
    if (cursor.hasNext()) {
        cursor.advance();
    } else {
        cursor.select(0);
    }
    return true;
}

RepeatModeKind RepeatAllMode::identify() const {
    return RepeatModeKind::All;
}