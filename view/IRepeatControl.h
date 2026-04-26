#ifndef I_REPEAT_CONTROL_H
#define I_REPEAT_CONTROL_H

class IRepeatControl {
public:
    virtual ~IRepeatControl() = default;
    virtual void onRepeat() = 0;
};

#endif //I_REPEAT_CONTROL_H