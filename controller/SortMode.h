#ifndef SORT_MODE_H
#define SORT_MODE_H

#include <string>
#include <memory>
#include "../model/service/Setlist.h"
#include "../view/IControlPanel.h"
#include "../model/ISortingAlgorithm.h"

class SortMode {
private:
    std::string label_;

protected:
    std::unique_ptr<ISortingAlgorithm> criteria_;

public:
    SortMode(const std::string& label, ISortingAlgorithm* criteria);
    virtual ~SortMode() = default;
    virtual void apply(Setlist& setlist);
    void display(IControlPanel& control) const;
};

#endif //SORT_MODE_H