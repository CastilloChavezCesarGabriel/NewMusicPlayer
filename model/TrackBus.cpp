#include "TrackBus.h"

void TrackBus::add(ITrackListener& listener) {
    listeners_.push_back(&listener);
}

void TrackBus::notify(const std::function<void(ITrackListener*)>& action) const {
    for (auto* listener : listeners_) {
        action(listener);
    }
}

void TrackBus::onStart(const std::string& path) {
    notify([&](ITrackListener* listener) { listener->onStart(path); });
}

void TrackBus::onSelected(const int index) {
    notify([&](ITrackListener* listener) { listener->onSelected(index); });
}

void TrackBus::onStopped() {
    notify([](ITrackListener* listener) { listener->onStopped(); });
}
