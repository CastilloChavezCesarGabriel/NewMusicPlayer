#include "Tracklist.h"

Tracklist::Tracklist() = default;

void Tracklist::add(const Song& song) {
    songs_.push_back(song);
    original_order_.invalidate();
}

void Tracklist::remove(const int index, IPathVisitor& receiver) {
    if (index < 0 || index >= static_cast<int>(songs_.size())) return;
    songs_[index].dispatch(receiver);
    songs_.erase(songs_.begin() + index);
    original_order_.invalidate();
    for (IRemovalListener* listener : removal_listeners_) {
        listener->onRemove(index);
    }
}

void Tracklist::reorder(IArrangementStrategy& strategy) {
    original_order_.preserve(songs_);
    strategy.arrange(songs_);
}

void Tracklist::restore() {
    original_order_.restore(songs_);
}

void Tracklist::accept(ISongVisitor& visitor) const {
    for (const Song& song : songs_) {
        song.accept(visitor);
    }
}

void Tracklist::filter(const std::string& query, ISongVisitor& visitor) const {
    for (const Song& song : songs_) {
        if (song.matches(query)) {
            song.accept(visitor);
        }
    }
}

void Tracklist::dispatch(const int index, IPathVisitor& visitor) const {
    if (existsAt(index)) {
        songs_[index].dispatch(visitor);
    }
}

int Tracklist::chase(const int index, const std::function<void()>& operation) const {
    if (!existsAt(index)) {
        operation();
        return -1;
    }
    const Song current = songs_[index];
    operation();
    for (int i = 0; i < static_cast<int>(songs_.size()); i++) {
        if (songs_[i].equals(current)) {
            return i;
        }
    }
    return -1;
}

bool Tracklist::existsAt(const int index) const {
    return index >= 0 && index < static_cast<int>(songs_.size());
}

bool Tracklist::existsAfter(const int index) const {
    return index + 1 < static_cast<int>(songs_.size());
}

std::optional<int> Tracklist::find(const std::string& name) const {
    for (int index = 0; index < static_cast<int>(songs_.size()); index++) {
        if (songs_[index].matches(name)) {
            return index;
        }
    }
    return std::nullopt;
}

void Tracklist::subscribe(IRemovalListener& listener) {
    removal_listeners_.push_back(&listener);
}