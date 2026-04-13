#ifndef I_PLAYBACK_CONTROL_H
#define I_PLAYBACK_CONTROL_H

class IPlaybackControl {
public:
    virtual ~IPlaybackControl() = default;
    virtual void onPlay(int index) = 0;
    virtual void onToggle() = 0;
    virtual void onAdvance() = 0;
    virtual void onRetreat() = 0;
};

#endif //I_PLAYBACK_CONTROL_H