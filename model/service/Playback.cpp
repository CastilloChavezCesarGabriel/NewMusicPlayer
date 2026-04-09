#include "Playback.h"

Playback::Playback(Playlist& playlist, Advertisement& advertisement, RepeatMode& repeat_mode)
    : playlist_(playlist), advertisement_(advertisement), repeat_mode_(repeat_mode) {}

void Playback::play(const int index) {
    playlist_.select(index);
    if (!advertisement_.interrupt()) {
        playlist_.play();
    }
}

void Playback::pick(const std::string& name) {
    playlist_.pick(name);
    if (!advertisement_.interrupt()) {
        playlist_.play();
    }
}

void Playback::advance() {
    if (playlist_.hasNext()) {
        playlist_.advance();
        playlist_.play();
    }
}

void Playback::retreat() {
    playlist_.retreat();
    playlist_.play();
}

void Playback::end() {
    if (advertisement_.conclude()) {
        playlist_.play();
        return;
    }
    if (repeat_mode_.apply()) {
        playlist_.play();
    } else {
        repeat_mode_.stop();
    }
}

void Playback::skip() {
    if (advertisement_.conclude()) {
        playlist_.play();
    }
}
