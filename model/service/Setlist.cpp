#include "Setlist.h"
#include "../tracklist/ShuffleStrategy.h"
#include "../tracklist/ReverseStrategy.h"

Setlist::Setlist(Tracklist& tracklist, TrackCursor& cursor, ILibraryListener& libraryEvents)
    : tracklist_(tracklist), cursor_(cursor), library_events_(libraryEvents) {}

void Setlist::shuffle() const {
    ShuffleStrategy strategy;
    run(strategy);
}

void Setlist::sort(IArrangementStrategy& criteria) const {
    run(criteria);
}

void Setlist::reverse() const {
    ReverseStrategy strategy;
    run(strategy);
}

void Setlist::restore() const {
    cursor_.chase([&] { tracklist_.restore(); });
    library_events_.onChanged();
}

void Setlist::rearrange(IArrangementStrategy& criteria) const {
    cursor_.chase([&] { tracklist_.reorder(criteria); });
}

void Setlist::run(IArrangementStrategy& strategy) const {
    rearrange(strategy);
    library_events_.onChanged();
}