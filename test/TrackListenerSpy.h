#ifndef TRACK_LISTENER_SPY_H
#define TRACK_LISTENER_SPY_H

#include "../model/event/ITrackListener.h"
#include <string>
#include <vector>

class TrackListenerSpy final : public ITrackListener {
private:
    std::vector<std::string> starts_;
    std::vector<int> selections_;

public:
    void onStart(const std::string& path) override;
    void onSelect(int index) override;
    void onStop() override;

    void expectStart() const;
    void expectStartWith(const std::string& path) const;
    void expectNoStart() const;
    void expectSelect() const;
    void expectSelectWith(int index) const;
    void expectNoSelect() const;
    void expectNoSelectWith(int index) const;
};

#endif //TRACK_LISTENER_SPY_H