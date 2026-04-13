#ifndef I_AUDIO_CONTROL_H
#define I_AUDIO_CONTROL_H

class IAudioControl {
public:
    virtual ~IAudioControl() = default;
    virtual void onAdjust(int volume) = 0;
    virtual void onEnd() = 0;
    virtual void onSkip() = 0;
};

#endif //I_AUDIO_CONTROL_H