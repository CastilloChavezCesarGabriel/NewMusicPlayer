#ifndef SETLIST_H
#define SETLIST_H

#include "../Playlist.h"
#include "../PlaybackNotifier.h"
#include "../SortingAlgorithm.h"

class Setlist {
private:
    Playlist& playlist_;
    PlaybackNotifier& notifier_;

public:
    Setlist(Playlist& playlist, PlaybackNotifier& notifier);

    void shuffle() const;
    void sort(SortingAlgorithm& criteria) const;
    void reverse() const;
    void restore() const;
};

#endif //SETLIST_H