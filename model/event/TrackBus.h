#ifndef TRACK_BUS_H
#define TRACK_BUS_H

#include "Bus.h"
#include "ITrackListener.h"

class TrackBus final : public Bus<ITrackListener>, public ITrackListener {
public:
    void onStart(const std::string& path) override;
    void onSelect(int index) override;
    void onStop() override;
};

#endif //TRACK_BUS_H