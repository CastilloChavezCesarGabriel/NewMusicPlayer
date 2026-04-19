#ifndef TRACKLIST_H
#define TRACKLIST_H

#include "../song/Song.h"
#include "OriginalOrder.h"
#include "../song/ISongVisitor.h"
#include "../song/IPathVisitor.h"
#include "IArrangementStrategy.h"
#include "IRemovalListener.h"
#include <vector>
#include <string>
#include <functional>

class Tracklist final : public ISongVisitor {
private:
    std::vector<Song> songs_;
    OriginalOrder original_order_;
    std::vector<IRemovalListener*> removal_listeners_;

public:
    Tracklist();

    void add(const Song& song);
    void remove(int index, IPathVisitor& receiver);
    void reorder(IArrangementStrategy& strategy);
    void restore();
    void accept(ISongVisitor& visitor) const;
    void visit(const std::string& name, const std::string& path) override;
    void filter(const std::string& query, ISongVisitor& visitor) const;
    void stream(int index, IPathVisitor& visitor) const;
    int follow(int index, const std::function<void()>& operation) const;
    bool hasAt(int index) const;
    bool hasAfter(int index) const;
    int find(const std::string& name) const;
    void subscribe(IRemovalListener& listener);
};

#endif //TRACKLIST_H