#ifndef TRACKLIST_H
#define TRACKLIST_H

#include "Song.h"
#include "OriginalOrder.h"
#include "ISongVisitor.h"
#include "IPathVisitor.h"
#include "IArrangementStrategy.h"
#include "IRemovalListener.h"
#include <vector>
#include <string>

class Tracklist {
private:
    std::vector<Song> songs_;
    OriginalOrder original_order_;
    std::vector<IRemovalListener*> removal_listeners_;

public:
    Tracklist();

    void add(const Song& song);
    void discard(int index, IPathVisitor& receiver);
    void clear();
    void arrange(IArrangementStrategy& strategy);
    void restore();
    void accept(ISongVisitor& visitor) const;
    void search(const std::string& query, ISongVisitor& visitor) const;
    void feed(int index, ISongVisitor& visitor) const;
    void stream(int index, IPathVisitor& visitor) const;
    bool hasAt(int index) const;
    bool hasAfter(int index) const;
    int find(const std::string& name) const;
    void subscribe(IRemovalListener& listener);
};

#endif //TRACKLIST_H