#ifndef TRANSPORT_CONTROLLER_H
#define TRANSPORT_CONTROLLER_H

#include "../model/service/PlaybackTransport.h"
#include "../view/IPlaybackControl.h"
#include "../view/IAudioControl.h"
#include "../view/IAudioPlayer.h"
#include "../view/ISearchPanel.h"

class TransportController final : public IPlaybackControl, public IAudioControl {
private:
    PlaybackTransport& playback_;
    IAudioPlayer& audio_;
    ISearchPanel& search_;
    bool playing_ = false;

public:
    TransportController(PlaybackTransport& playback, IAudioPlayer& audio, ISearchPanel& search);
    void onPlay(int index) override;
    void onToggle() override;
    void onAdvance() override;
    void onRetreat() override;
    bool onSkip() override;
    void onEnd() override;
    void onAdjust(int volume) override;
};

#endif //TRANSPORT_CONTROLLER_H