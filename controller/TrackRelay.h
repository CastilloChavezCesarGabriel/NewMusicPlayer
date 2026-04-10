#ifndef TRACK_RELAY_H
#define TRACK_RELAY_H

#include "../model/ITrackListener.h"
#include "../view/IAudioPlayer.h"
#include "../view/IPlaylistPanel.h"
#include "../view/IControlPanel.h"

class TrackRelay final : public ITrackListener {
private:
    IAudioPlayer& audio_;
    IPlaylistPanel& panel_;
    IControlPanel& control_;

public:
    TrackRelay(IAudioPlayer& audio, IPlaylistPanel& panel, IControlPanel& control);
    void onStart(const std::string& path) override;
    void onSelected(int index) override;
    void onStopped() override;
};

#endif //TRACK_RELAY_H