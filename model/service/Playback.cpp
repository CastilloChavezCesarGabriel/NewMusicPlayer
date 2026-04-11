#include "Playback.h"

Playback::Playback(Cursor& cursor, Advertisement& advertisement, RepeatMode& repeat_mode)
    : cursor_(cursor), advertisement_(advertisement), repeat_mode_(repeat_mode) {}

void Playback::start() const {
    if (!advertisement_.interrupt()) {
        cursor_.play();
    }
}

void Playback::play(const int index) const {
    cursor_.select(index);
    start();
}

void Playback::pick(const std::string& name) const {
    cursor_.pick(name);
    start();
}

void Playback::advance() const {
    if (cursor_.hasNext()) {
        cursor_.advance();
        cursor_.play();
    }
}

void Playback::retreat() const {
    cursor_.retreat();
    cursor_.play();
}

void Playback::end() const {
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

void Playback::skip() const {
    if (advertisement_.conclude()) {
        cursor_.play();
    }
}