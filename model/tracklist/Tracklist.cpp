#include "Tracklist.h"

Tracklist::Tracklist() = default;

void Tracklist::visit(const std::string& name, const std::string& path) {
    add(Song(name, path));
}

void Tracklist::add(const Song& song) {
    songs_.push_back(song);
    original_order_.invalidate();
}

void Tracklist::discard(const int index, IPathVisitor& receiver) {
    if (index < 0 || index >= static_cast<int>(songs_.size())) return;
    songs_[index].stream(receiver);
    songs_.erase(songs_.begin() + index);
    original_order_.invalidate();
    for (IRemovalListener* listener : removal_listeners_) {
        listener->onRemoved(index);
    }
}

void Tracklist::arrange(IArrangementStrategy& strategy) {
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

void Tracklist::search(const std::string& query, ISongVisitor& visitor) const {
    for (const Song& song : songs_) {
        if (song.matches(query)) {
            song.accept(visitor);
        }
    }
}

void Tracklist::stream(const int index, IPathVisitor& visitor) const {
    if (hasAt(index)) {
        songs_[index].stream(visitor);
    }
}

int Tracklist::pin(const int index, const std::function<void()>& operation) const {
    if (!hasAt(index)) {
        operation();
        return -1;
    }
    const Song current = songs_[index];
    operation();
    for (int i = 0; i < static_cast<int>(songs_.size()); i++) {
        if (songs_[i].identifies(current)) {
            return i;
        }
    }
    return -1;
}

bool Tracklist::hasAt(const int index) const {
    return index >= 0 && index < static_cast<int>(songs_.size());
}

bool Tracklist::hasAfter(const int index) const {
    return index + 1 < static_cast<int>(songs_.size());
}

int Tracklist::find(const std::string& name) const {
    for (int index = 0; index < static_cast<int>(songs_.size()); index++) {
        if (songs_[index].matches(name)) {
            return index;
        }
    }
    return -1;
}

void Tracklist::subscribe(IRemovalListener& listener) {
    removal_listeners_.push_back(&listener);
}