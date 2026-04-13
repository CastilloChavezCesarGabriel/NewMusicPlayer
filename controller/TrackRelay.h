#ifndef TRACK_RELAY_H
#define TRACK_RELAY_H

#include "../model/event/ITrackListener.h"
#include "../view/IAudioPlayer.h"
#include "../view/IPlaylistPanel.h"
#include "../view/IEnableable.h"

class TrackRelay final : public ITrackListener {
private:
    IAudioPlayer& audio_;
    IPlaylistPanel& panel_;
    IEnableable& enable_;

public:
    TrackRelay(IAudioPlayer& audio, IPlaylistPanel& panel, IEnableable& enable);
    void onStart(const std::string& path) override;
    void onSelected(int index) override;
    void onStopped() override;
};

#endif //TRACK_RELAY_H