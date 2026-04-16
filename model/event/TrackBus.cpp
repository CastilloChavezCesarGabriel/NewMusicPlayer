#include "TrackBus.h"

void TrackBus::onStart(const std::string& path) {
    broadcast([&](ITrackListener& listener) { listener.onStart(path); });
}

void TrackBus::onSelect(const int index) {
    broadcast([&](ITrackListener& listener) { listener.onSelect(index); });
}

void TrackBus::onStop() {
    broadcast([](ITrackListener& listener) { listener.onStop(); });
}