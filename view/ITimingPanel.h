#ifndef I_TIMING_PANEL_H
#define I_TIMING_PANEL_H

class ITimingPanel {
public:
    virtual ~ITimingPanel() = default;
    virtual void schedule(int delay) = 0;
    virtual void cancel() = 0;
};

#endif