#include "Playlist.h"
#include "PlaybackNotifier.h"
#include "Channel.h"
#include <random>
#include <algorithm>
#include <ranges>

Playlist::Playlist(IPlaylistVisitor& deleter, PlaybackNotifier& notifier)
    : deleter_(deleter), notifier_(notifier) {}

void Playlist::add(const Song& song) {
    songs_.push_back(song);
}

void Playlist::remove(const int index) {
    if (index < 0 || index >= songs_.size()) return;
    songs_[index].accept(deleter_);
    songs_.erase(songs_.begin() + index);

    if (index == current_song_) {
        current_song_ = -1;
    } else if (index < current_song_) {
        current_song_--;
    }
}

void Playlist::sort(SortingAlgorithm& criteria) {
    rearrange([&] { arrangement_.sort(songs_, criteria); });
}

void Playlist::reverse() {
    rearrange([this] { arrangement_.reverse(songs_); });
}

void Playlist::restore() {
    rearrange([this] { arrangement_.restore(songs_); });
}

void Playlist::rearrange(const std::function<void()>& operation) {
    if (!hasSelected()) {
        operation();
        return;
    }
    const Song current = songs_[current_song_];
    operation();
    locate(current);
}

void Playlist::locate(const Song& target) {
    for (int index = 0; index < songs_.size(); index++) {
        if (songs_[index].isEqualTo(target)) {
            current_song_ = index;
            return;
        }
    }
    current_song_ = -1;
}

void Playlist::shuffle() {
    static std::random_device device;
    static std::mt19937 generator(device());

    if (hasSelected()) {
        std::swap(songs_[0], songs_[current_song_]);
        std::shuffle(songs_.begin() + 1, songs_.end(), generator);
        current_song_ = 0;
    } else {
        std::ranges::shuffle(songs_, generator);
    }
}

void Playlist::clear() {
    songs_.clear();
    current_song_ = -1;
}

void Playlist::select(const int index) {
    if (index >= 0 && index < songs_.size()) {
        current_song_ = index;
        notify();
    }
}

void Playlist::pick(const std::string& name) {
    for (int index = 0; index < songs_.size(); index++) {
        if (songs_[index].matches(name)) {
            select(index);
            return;
        }
    }
}

void Playlist::advance() {
    if (hasNext()) {
        current_song_++;
        notify();
    }
}

void Playlist::retreat() {
    if (current_song_ > 0) {
        current_song_--;
        notify();
    }
}

void Playlist::notify() const {
    notifier_.onSelected(current_song_);
}

void Playlist::play() const {
    if (hasSelected()) {
        Channel channel(notifier_);
        songs_[current_song_].accept(channel);
    }
}

void Playlist::accept(IPlaylistVisitor& visitor) const {
    for (const Song& song : songs_) {
        song.accept(visitor);
    }
}

void Playlist::search(const std::string& query, IPlaylistVisitor& visitor) const {
    for (const Song& song : songs_) {
        if (song.matches(query)) {
            song.accept(visitor);
        }
    }
}

bool Playlist::hasNext() const {
    return current_song_ + 1 < static_cast<int>(songs_.size());
}

bool Playlist::hasSelected() const {
    return current_song_ >= 0 && current_song_ < static_cast<int>(songs_.size());
}