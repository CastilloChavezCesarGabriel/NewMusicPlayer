#include "TrackCursor.h"
#include "../song/SongStartAnnouncer.h"

TrackCursor::TrackCursor(Tracklist& tracklist, ITrackListener& tracks)
    : tracklist_(tracklist), tracks_(tracks) {
    tracklist_.subscribe(*this);
}

void TrackCursor::select(const int index) {
    if (tracklist_.existsAt(index)) {
        track_index_ = index;
        notify();
    }
}

void TrackCursor::pick(const std::string& name) {
    if (const auto index = tracklist_.find(name)) {
        select(*index);
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
        tracklist_.dispatch(track_index_, announcer);
    }
}

bool TrackCursor::hasNext() const {
    return tracklist_.existsAfter(track_index_);
}

bool TrackCursor::hasSelected() const {
    return tracklist_.existsAt(track_index_);
}

void TrackCursor::chase(const std::function<void()>& operation) {
    track_index_ = tracklist_.chase(track_index_, operation);
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