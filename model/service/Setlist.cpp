#include "Setlist.h"

Setlist::Setlist(Playlist& playlist, PlaybackNotifier& notifier)
    : playlist_(playlist), notifier_(notifier) {}

void Setlist::shuffle() const {
    playlist_.shuffle();
    notifier_.onChanged();
}

void Setlist::sort(SortingAlgorithm& criteria) const {
    playlist_.sort(criteria);
    notifier_.onChanged();
}

void Setlist::reverse() const {
    playlist_.reverse();
    notifier_.onChanged();
}

void Setlist::restore() const {
    playlist_.restore();
    notifier_.onChanged();
}