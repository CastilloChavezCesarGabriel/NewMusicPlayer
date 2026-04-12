#include "TransportController.h"

TransportController::TransportController(PlaybackService& playback, IAudioPlayer& audio, ISearchPanel& search)
    : playback_(playback), audio_(audio), search_(search) {}

void TransportController::onPlay(const int index) {
    playback_.play(index);
}

void TransportController::onToggle() {
    if (playing_) {
        audio_.pause();
    } else {
        audio_.resume();
    }
    playing_ = !playing_;
}

void TransportController::onAdvance() {
    playback_.advance();
}

void TransportController::onRetreat() {
    playback_.retreat();
}

void TransportController::onSkip() {
    playback_.skip();
}

void TransportController::onEnd() {
    playback_.end();
}

void TransportController::onAdjust(const int volume) {
    audio_.adjust(volume);
}