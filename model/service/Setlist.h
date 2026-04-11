#ifndef SETLIST_H
#define SETLIST_H

#include "../Tracklist.h"
#include "../Cursor.h"
#include "../ILibraryListener.h"
#include "../IArrangementStrategy.h"

class Setlist {
private:
    Tracklist& tracklist_;
    Cursor& cursor_;
    ILibraryListener& library_events_;

    void run(IArrangementStrategy& strategy) const;

public:
    Setlist(Tracklist& tracklist, Cursor& cursor, ILibraryListener& library_events);

    void shuffle() const;
    void sort(IArrangementStrategy& criteria) const;
    void reverse() const;
    void restore() const;
};

#endif //SETLIST_H
