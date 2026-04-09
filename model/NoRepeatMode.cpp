#include "NoRepeatMode.h"

NoRepeatMode::NoRepeatMode() : RepeatStrategy(0) {}

bool NoRepeatMode::apply(Playlist& playlist) {
    if (!playlist.hasNext()) return false;
    playlist.advance();
    return true;
}
