#ifndef I_REPEAT_DISPLAY_H
#define I_REPEAT_DISPLAY_H

#include "IEnableable.h"

class IRepeatDisplay : public IEnableable {
public:
    virtual void repeat(int mode) = 0;
};

#endif
