#include "PlaybackTransport.h"

PlaybackTransport::PlaybackTransport(TrackCursor& cursor, AdScheduler& advertisement, RepeatPolicy& repeatMode)
    : cursor_(cursor), advertisement_(advertisement), repeat_mode_(repeatMode) {}

void PlaybackTransport::start() const {
    if (!advertisement_.interrupt()) {
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
    if (advertisement_.conclude()) {
        cursor_.play();
        return;
    }

    if (repeat_mode_.apply()) {
        cursor_.play();
    } else {
        repeat_mode_.stop();
    }
}

void PlaybackTransport::skip() const {
    if (advertisement_.conclude()) {
        cursor_.play();
    }
}