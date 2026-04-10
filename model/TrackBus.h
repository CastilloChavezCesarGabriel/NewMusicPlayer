#ifndef TRACK_BUS_H
#define TRACK_BUS_H

#include "ITrackListener.h"
#include <vector>
#include <functional>

class TrackBus final : public ITrackListener {
private:
    std::vector<ITrackListener*> listeners_;
    void notify(const std::function<void(ITrackListener*)>& action) const;

public:
    void add(ITrackListener& listener);
    void onStart(const std::string& path) override;
    void onSelected(int index) override;
    void onStopped() override;
};

#endif //TRACK_BUS_H
