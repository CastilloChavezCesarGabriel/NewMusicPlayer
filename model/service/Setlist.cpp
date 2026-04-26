#include "Setlist.h"
#include "../tracklist/ShuffleStrategy.h"
#include "../tracklist/ReverseStrategy.h"

Setlist::Setlist(Tracklist& tracklist, TrackCursor& cursor, ILibraryListener& libraryEvents)
    : tracklist_(tracklist), cursor_(cursor), library_events_(libraryEvents) {}

void Setlist::shuffle() const {
    ShuffleStrategy strategy;
    arrange(strategy);
}

void Setlist::sort(IArrangementStrategy& criteria) const {
    arrange(criteria);
}

void Setlist::reverse() const {
    ReverseStrategy strategy;
    arrange(strategy);
}

void Setlist::restore() const {
    cursor_.chase([&] { tracklist_.restore(); });
}

void Setlist::announce() const {
    library_events_.onChanged();
}

void Setlist::arrange(IArrangementStrategy& strategy) const {
    cursor_.chase([&] { tracklist_.reorder(strategy); });
}