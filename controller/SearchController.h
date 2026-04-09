#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "../model/service/Catalog.h"
#include "../view/IPlayerView.h"
#include <string>

class SearchController {
private:
    Catalog& catalog_;
    IPlayerView& view_;

public:
    SearchController(Catalog& catalog, IPlayerView& view);
    void search(const std::string& query) const;
};

#endif //SEARCH_CONTROLLER_H
