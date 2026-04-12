#include "TrackCursor.h"
#include "../song/Channel.h"

TrackCursor::TrackCursor(Tracklist& tracklist, ITrackListener& tracks)
    : tracklist_(tracklist), tracks_(tracks) {
    tracklist_.subscribe(*this);
}

void TrackCursor::select(const int index) {
    if (tracklist_.hasAt(index)) {
        index_ = index;
        notify();
    }
}

void TrackCursor::pick(const std::string& name) {
    const int index = tracklist_.find(name);
    if (index >= 0) {
        select(index);
    }
}

void TrackCursor::advance() {
    if (hasNext()) {
        index_++;
        notify();
    }
}

void TrackCursor::retreat() {
    if (index_ > 0) {
        index_--;
        notify();
    }
}

void TrackCursor::play() const {
    if (hasSelected()) {
        Channel channel(tracks_);
        tracklist_.stream(index_, channel);
    }
}

bool TrackCursor::hasNext() const {
    return tracklist_.hasAfter(index_);
}

bool TrackCursor::hasSelected() const {
    return tracklist_.hasAt(index_);
}

void TrackCursor::pin(const std::function<void()>& operation) {
    index_ = tracklist_.pin(index_, operation);
}

void TrackCursor::clear() {
    index_ = -1;
}

void TrackCursor::onRemoved(const int index) {
    if (index == index_) {
        clear();
    } else if (index < index_) {
        index_--;
    }
}

void TrackCursor::notify() const {
    tracks_.onSelected(index_);
}