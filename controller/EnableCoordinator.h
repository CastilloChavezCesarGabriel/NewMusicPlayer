#ifndef ENABLE_COORDINATOR_H
#define ENABLE_COORDINATOR_H

#include "../view/IEnableable.h"
#include <vector>

class EnableCoordinator final : public IEnableable {
private:
    std::vector<IEnableable*> targets_;

public:
    void add(IEnableable& target);
    void enable(bool state) override;
};

#endif