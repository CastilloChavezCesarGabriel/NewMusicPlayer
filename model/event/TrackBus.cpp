#include "TrackBus.h"

void TrackBus::onStart(const std::string& path) {
    broadcast([&](ITrackListener& listener) { listener.onStart(path); });
}

void TrackBus::onSelected(const int index) {
    broadcast([&](ITrackListener& listener) { listener.onSelected(index); });
}

void TrackBus::onStopped() {
    broadcast([](ITrackListener& listener) { listener.onStopped(); });
}