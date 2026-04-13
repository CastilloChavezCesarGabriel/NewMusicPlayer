#include "TrackCursor.h"
#include "../song/Channel.h"

TrackCursor::TrackCursor(Tracklist& tracklist, ITrackListener& tracks)
    : tracklist_(tracklist), tracks_(tracks) {
    tracklist_.subscribe(*this);
}

void TrackCursor::select(const int index) {
    if (tracklist_.hasAt(index)) {
        track_index_ = index;
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
        track_index_++;
        notify();
    }
}

void TrackCursor::retreat() {
    if (track_index_ > 0) {
        track_index_--;
        notify();
    }
}

void TrackCursor::play() const {
    if (hasSelected()) {
        Channel channel(tracks_);
        tracklist_.stream(track_index_, channel);
    }
}

bool TrackCursor::hasNext() const {
    return tracklist_.hasAfter(track_index_);
}

bool TrackCursor::hasSelected() const {
    return tracklist_.hasAt(track_index_);
}

void TrackCursor::pin(const std::function<void()>& operation) {
    track_index_ = tracklist_.pin(track_index_, operation);
}

void TrackCursor::clear() {
    track_index_ = -1;
}

void TrackCursor::onRemoved(const int index) {
    if (index == track_index_) {
        clear();
    } else if (index < track_index_) {
        track_index_--;
    }
}

void TrackCursor::notify() const {
    tracks_.onSelected(track_index_);
}