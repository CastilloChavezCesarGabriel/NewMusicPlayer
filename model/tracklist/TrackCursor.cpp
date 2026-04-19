#include "TrackCursor.h"
#include "../song/SongStartAnnouncer.h"

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
        SongStartAnnouncer announcer(tracks_);
        tracklist_.stream(track_index_, announcer);
    }
}

bool TrackCursor::hasNext() const {
    return tracklist_.hasAfter(track_index_);
}

bool TrackCursor::hasSelected() const {
    return tracklist_.hasAt(track_index_);
}

void TrackCursor::follow(const std::function<void()>& operation) {
    track_index_ = tracklist_.follow(track_index_, operation);
}

void TrackCursor::onRemove(const int index) {
    if (index == track_index_) {
        track_index_ = -1;
    } else if (index < track_index_) {
        track_index_--;
    }
}

void TrackCursor::notify() const {
    tracks_.onSelect(track_index_);
}