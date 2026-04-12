#include "PlaybackService.h"

PlaybackService::PlaybackService(TrackCursor& cursor, Advertisement& advertisement, RepeatMode& repeat_mode)
    : cursor_(cursor), advertisement_(advertisement), repeat_mode_(repeat_mode) {}

void PlaybackService::start() const {
    if (!advertisement_.interrupt()) {
        cursor_.play();
    }
}

void PlaybackService::play(const int index) const {
    cursor_.select(index);
    start();
}

void PlaybackService::pick(const std::string& name) const {
    cursor_.pick(name);
    start();
}

void PlaybackService::advance() const {
    if (cursor_.hasNext()) {
        cursor_.advance();
        cursor_.play();
    }
}

void PlaybackService::retreat() const {
    cursor_.retreat();
    cursor_.play();
}

void PlaybackService::end() const {
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

void PlaybackService::skip() const {
    if (advertisement_.conclude()) {
        cursor_.play();
    }
}