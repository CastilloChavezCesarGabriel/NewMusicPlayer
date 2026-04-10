#include "Cursor.h"
#include "Channel.h"
#include "ISongVisitor.h"

namespace {
    class NameCapture final : public ISongVisitor {
    private:
        std::string& target_;
    public:
        explicit NameCapture(std::string& target) : target_(target) {}
        void visit(const std::string& name, const std::string&) override {
            target_ = name;
        }
    };
}

Cursor::Cursor(Tracklist& tracklist, ITrackListener& tracks)
    : tracklist_(tracklist), tracks_(tracks) {
    tracklist_.subscribe(*this);
}

void Cursor::select(const int index) {
    if (tracklist_.hasAt(index)) {
        index_ = index;
        notify();
    }
}

void Cursor::pick(const std::string& name) {
    const int index = tracklist_.find(name);
    if (index >= 0) {
        select(index);
    }
}

void Cursor::advance() {
    if (hasNext()) {
        index_++;
        notify();
    }
}

void Cursor::retreat() {
    if (index_ > 0) {
        index_--;
        notify();
    }
}

void Cursor::play() const {
    if (hasSelected()) {
        Channel channel(tracks_);
        tracklist_.stream(index_, channel);
    }
}

bool Cursor::hasNext() const {
    return tracklist_.hasAfter(index_);
}

bool Cursor::hasSelected() const {
    return tracklist_.hasAt(index_);
}

void Cursor::pin(const std::function<void()>& operation) {
    if (!hasSelected()) {
        operation();
        return;
    }
    std::string current_name;
    NameCapture capture(current_name);
    tracklist_.feed(index_, capture);
    operation();
    index_ = tracklist_.find(current_name);
}

void Cursor::clear() {
    index_ = -1;
}

void Cursor::onRemoved(const int index) {
    if (index == index_) {
        index_ = -1;
    } else if (index < index_) {
        index_--;
    }
}

void Cursor::notify() const {
    tracks_.onSelected(index_);
}