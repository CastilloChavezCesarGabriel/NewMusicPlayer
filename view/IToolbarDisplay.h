#ifndef I_TOOLBAR_DISPLAY_H
#define I_TOOLBAR_DISPLAY_H

class IToolbarDisplay {
public:
    virtual ~IToolbarDisplay() = default;
    virtual void enable(bool state) = 0;
    virtual void reveal(bool visible) = 0;
};

#endif