#ifndef SETLIST_H
#define SETLIST_H

#include "../tracklist/Tracklist.h"
#include "../tracklist/TrackCursor.h"
#include "../event/ILibraryListener.h"
#include "../tracklist/IArrangementStrategy.h"

class Setlist {
private:
    Tracklist& tracklist_;
    TrackCursor& cursor_;
    ILibraryListener& library_events_;

    void arrange(IArrangementStrategy& strategy) const;

public:
    Setlist(Tracklist& tracklist, TrackCursor& cursor, ILibraryListener& libraryEvents);

    void shuffle() const;
    void sort(IArrangementStrategy& criteria) const;
    void reverse() const;
    void restore() const;
    void announce() const;
};

#endif //SETLIST_H