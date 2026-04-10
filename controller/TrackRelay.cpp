#include "TrackRelay.h"

TrackRelay::TrackRelay(IAudioPlayer& audio, IPlaylistPanel& panel, IEnableable& enable)
    : audio_(audio), panel_(panel), enable_(enable) {}

void TrackRelay::onStart(const std::string& path) {
    audio_.play(path);
}

void TrackRelay::onSelected(const int index) {
    panel_.highlight(index);
    enable_.enable(true);
}

void TrackRelay::onStopped() {
    enable_.enable(false);
    audio_.pause();
    panel_.highlight(-1);
}
