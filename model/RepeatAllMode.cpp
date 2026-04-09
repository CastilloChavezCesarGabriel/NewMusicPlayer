#include "RepeatAllMode.h"

RepeatAllMode::RepeatAllMode() : RepeatStrategy(2) {}

bool RepeatAllMode::apply(Playlist& playlist) {
    if (playlist.hasNext()) {
        playlist.advance();
    } else {
        playlist.select(0);
    }
    return true;
}
