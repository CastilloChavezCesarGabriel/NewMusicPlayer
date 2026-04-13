#ifndef I_PLAYBACK_DISPLAY_H
#define I_PLAYBACK_DISPLAY_H

class IPlaybackDisplay {
public:
    virtual ~IPlaybackDisplay() = default;
    virtual void enable(bool state) = 0;
    virtual void toggle(bool playing) = 0;
};

#endif