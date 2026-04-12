#ifndef ENABLE_GROUP_H
#define ENABLE_GROUP_H

#include "../view/IEnableable.h"
#include <vector>

class EnableGroup final : public IEnableable {
private:
    std::vector<IEnableable*> targets_;

public:
    void add(IEnableable& target);
    void enable(bool state) override;
};

#endif