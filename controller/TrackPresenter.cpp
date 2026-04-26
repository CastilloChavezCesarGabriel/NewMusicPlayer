#include "TrackPresenter.h"

TrackPresenter::TrackPresenter(IAudioPlayer& audio, IPlaylistPanel& panel, IEnableable& enable)
    : audio_(audio), panel_(panel), enable_(enable) {}

void TrackPresenter::onStart(const std::string& path) {
    audio_.play(path);
}

void TrackPresenter::onSelect(const int index) {
    panel_.highlight(index);
    enable_.enable(true);
}

void TrackPresenter::onStop() {
    enable_.enable(false);
    audio_.pause();
    panel_.highlight(-1);
}