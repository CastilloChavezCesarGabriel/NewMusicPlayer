#include "Setlist.h"
#include "../tracklist/ShuffleArrangement.h"
#include "../tracklist/ReverseArrangement.h"

Setlist::Setlist(Tracklist& tracklist, Cursor& cursor, ILibraryListener& library_events)
    : tracklist_(tracklist), cursor_(cursor), library_events_(library_events) {}

void Setlist::shuffle() const {
    ShuffleArrangement strategy;
    run(strategy);
}

void Setlist::sort(IArrangementStrategy& criteria) const {
    run(criteria);
}

void Setlist::reverse() const {
    ReverseArrangement strategy;
    run(strategy);
}

void Setlist::restore() const {
    cursor_.pin([&] {
        tracklist_.restore();
    });
    library_events_.onChanged();
}

void Setlist::run(IArrangementStrategy& strategy) const {
    cursor_.pin([&] {
        tracklist_.arrange(strategy);
    });
    library_events_.onChanged();
}
