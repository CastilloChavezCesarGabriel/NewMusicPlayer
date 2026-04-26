#include "RepeatBroadcaster.h"

RepeatBroadcaster::RepeatBroadcaster(IRepeatListener& repeats, ITrackListener& tracks)
    : repeats_(repeats), tracks_(tracks) {}

void RepeatBroadcaster::onChanged(const RepeatModeKind kind) {
    repeats_.onChanged(kind);
}

void RepeatBroadcaster::stop() const {
    tracks_.onStop();
}