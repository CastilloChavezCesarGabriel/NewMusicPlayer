#include "Cursor.h"
#include "../song/Channel.h"

Cursor::Cursor(Tracklist& tracklist, ITrackListener& tracks)
    : tracklist_(tracklist), tracks_(tracks) {
    tracklist_.subscribe(*this);
}

void Cursor::select(const int index) {
    if (tracklist_.hasAt(index)) {
        index_ = index;
        notify();
    }
}

void Cursor::pick(const std::string& name) {
    const int index = tracklist_.find(name);
    if (index >= 0) {
        select(index);
    }
}

void Cursor::advance() {
    if (hasNext()) {
        index_++;
        notify();
    }
}

void Cursor::retreat() {
    if (index_ > 0) {
        index_--;
        notify();
    }
}

void Cursor::play() const {
    if (hasSelected()) {
        Channel channel(tracks_);
        tracklist_.stream(index_, channel);
    }
}

bool Cursor::hasNext() const {
    return tracklist_.hasAfter(index_);
}

bool Cursor::hasSelected() const {
    return tracklist_.hasAt(index_);
}

void Cursor::pin(const std::function<void()>& operation) {
    index_ = tracklist_.pin(index_, operation);
}

void Cursor::clear() {
    index_ = -1;
}

void Cursor::onRemoved(const int index) {
    if (index == index_) {
        clear();
    } else if (index < index_) {
        index_--;
    }
}

void Cursor::notify() const {
    tracks_.onSelected(index_);
}