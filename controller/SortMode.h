#ifndef SORT_MODE_H
#define SORT_MODE_H

#include <string>
#include <memory>
#include "../model/service/Setlist.h"
#include "../view/ISortDisplay.h"
#include "../model/tracklist/IArrangementStrategy.h"

class SortMode {
private:
    std::string label_;

protected:
    std::unique_ptr<IArrangementStrategy> criteria_;

public:
    SortMode(const std::string& label, std::unique_ptr<IArrangementStrategy> criteria);
    virtual ~SortMode() = default;
    virtual void apply(Setlist& setlist);
    void display(ISortDisplay& sortDisplay) const;
};

#endif //SORT_MODE_H