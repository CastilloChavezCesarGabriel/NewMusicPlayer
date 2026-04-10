#include "TrackRelay.h"

TrackRelay::TrackRelay(IAudioPlayer& audio, IPlaylistPanel& panel, IControlPanel& control)
    : audio_(audio), panel_(panel), control_(control) {}

void TrackRelay::onStart(const std::string& path) {
    audio_.play(path);
}

void TrackRelay::onSelected(const int index) {
    panel_.highlight(index);
    control_.enable(true);
}

void TrackRelay::onStopped() {
    control_.enable(false);
    audio_.pause();
    panel_.highlight(-1);
}