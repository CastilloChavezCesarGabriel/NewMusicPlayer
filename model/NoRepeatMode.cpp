#include "NoRepeatMode.h"

bool NoRepeatMode::apply(Cursor& cursor) {
    if (!cursor.hasNext()) return false;
    cursor.advance();
    return true;
}

RepeatModeKind NoRepeatMode::identify() const {
    return RepeatModeKind::None;
}
