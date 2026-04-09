#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include "SortingAlgorithm.h"
#include "IPlaylistVisitor.h"
#include "PlaybackNotifier.h"
#include "Arrangement.h"
#include <vector>
#include <functional>

class Playlist {
private:
    std::vector<Song> songs_;
    Arrangement arrangement_;
    IPlaylistVisitor& deleter_;
    PlaybackNotifier& notifier_;
    int current_song_ = -1;

public:
    Playlist(IPlaylistVisitor& deleter, PlaybackNotifier& notifier);

    void add(const Song& song);
    void remove(int index);
    void sort(SortingAlgorithm& criteria);
    void reverse();
    void restore();
    void shuffle();
    void clear();
    void select(int index);
    void pick(const std::string& name);
    void advance();
    void retreat();
    void play() const;
    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;
    bool hasNext() const;
    bool hasSelected() const;

private:
    void rearrange(const std::function<void()>& operation);
    void locate(const Song& target);
    void notify() const;
};

#endif //PLAYLIST_H