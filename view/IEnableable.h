#ifndef I_ENABLEABLE_H
#define I_ENABLEABLE_H

class IEnableable {
public:
    virtual ~IEnableable() = default;
    virtual void enable(bool state) = 0;
};

#endif