#include "OriginalOrder.h"

void OriginalOrder::preserve(const std::vector<Song>& songs) {
    if (snapshot_.empty()) {
        snapshot_ = songs;
    }
}

void OriginalOrder::restore(std::vector<Song>& songs) {
    if (snapshot_.empty()) return;
    songs = snapshot_;
    snapshot_.clear();
}

void OriginalOrder::invalidate() {
    snapshot_.clear();
}