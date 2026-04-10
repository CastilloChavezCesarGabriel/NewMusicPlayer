#ifndef REPEAT_MODE_H
#define REPEAT_MODE_H

#include "RepeatStrategy.h"
#include "Cursor.h"
#include "RepeatListener.h"
#include <vector>
#include <memory>

class RepeatMode {
private:
    Cursor& cursor_;
    RepeatListener& listener_;
    std::vector<std::unique_ptr<RepeatStrategy>> modes_;
    int index_ = 0;

public:
    RepeatMode(Cursor& cursor, RepeatListener& listener);
    void advance();
    bool apply() const;
    void stop() const;
};

#endif //REPEAT_MODE_H
