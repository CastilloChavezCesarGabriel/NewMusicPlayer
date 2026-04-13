#ifndef I_SORT_DISPLAY_H
#define I_SORT_DISPLAY_H

#include <string>

class ISortDisplay {
public:
    virtual ~ISortDisplay() = default;
    virtual void sort(const std::string& label) = 0;
};

#endif