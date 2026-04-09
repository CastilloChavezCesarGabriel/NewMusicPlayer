#ifndef MODELTEST_H
#define MODELTEST_H

#include "../ModelTestFixture.h"

class ModelTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif
