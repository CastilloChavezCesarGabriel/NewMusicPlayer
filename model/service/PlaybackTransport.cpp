#include "PlaybackTransport.h"

PlaybackTransport::PlaybackTransport(TrackCursor& cursor, AdScheduler& adScheduler, RepeatPolicy& repeatPolicy)
    : cursor_(cursor), ad_scheduler_(adScheduler), repeat_policy_(repeatPolicy) {}

void PlaybackTransport::start() const {
    if (!ad_scheduler_.interrupt()) {
        cursor_.play();
    }
}

void PlaybackTransport::play(const int index) const {
    cursor_.select(index);
    start();
}

void PlaybackTransport::pick(const std::string& name) const {
    cursor_.pick(name);
    start();
}

void PlaybackTransport::advance() const {
    if (cursor_.hasNext()) {
        cursor_.advance();
        cursor_.play();
    }
}

void PlaybackTransport::retreat() const {
    cursor_.retreat();
    cursor_.play();
}

void PlaybackTransport::end() const {
    if (resume()) return;

    if (repeat_policy_.apply()) {
        cursor_.play();
    } else {
        repeat_policy_.stop();
    }
}

bool PlaybackTransport::skip() const {
    return resume();
}

bool PlaybackTransport::resume() const {
    if (!ad_scheduler_.conclude()) return false;
    cursor_.play();
    return true;
}