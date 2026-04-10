#ifndef CURSOR_H
#define CURSOR_H

#include "Tracklist.h"
#include "ITrackListener.h"
#include "IRemovalListener.h"
#include <functional>
#include <string>

class Cursor final : public IRemovalListener {
private:
    Tracklist& tracklist_;
    ITrackListener& tracks_;
    int index_ = -1;

    void notify() const;

public:
    Cursor(Tracklist& tracklist, ITrackListener& tracks);

    void select(int index);
    void pick(const std::string& name);
    void advance();
    void retreat();
    void play() const;
    bool hasNext() const;
    bool hasSelected() const;
    void pin(const std::function<void()>& operation);
    void clear();
    void onRemoved(int index) override;
};

#endif //CURSOR_H
