#ifndef TRACK_PRESENTER_H
#define TRACK_PRESENTER_H

#include "../model/event/ITrackListener.h"
#include "../view/IAudioPlayer.h"
#include "../view/IPlaylistPanel.h"
#include "../view/IEnableable.h"

class TrackPresenter final : public ITrackListener {
private:
    IAudioPlayer& audio_;
    IPlaylistPanel& panel_;
    IEnableable& enable_;

public:
    TrackPresenter(IAudioPlayer& audio, IPlaylistPanel& panel, IEnableable& enable);
    void onStart(const std::string& path) override;
    void onSelect(int index) override;
    void onStop() override;
};

#endif //TRACK_PRESENTER_H