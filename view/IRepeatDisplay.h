#ifndef I_REPEAT_DISPLAY_H
#define I_REPEAT_DISPLAY_H

class IRepeatDisplay {
public:
    virtual ~IRepeatDisplay() = default;
    virtual void enable(bool state) = 0;
    virtual void repeat(int mode) = 0;
};

#endif
