#ifndef I_TOOLBAR_DISPLAY_H
#define I_TOOLBAR_DISPLAY_H

#include "IEnableable.h"

class IToolbarDisplay : public IEnableable {
public:
    virtual void reveal(bool visible) = 0;
};

#endif
