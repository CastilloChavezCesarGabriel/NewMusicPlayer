#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "../model/service/Catalog.h"
#include "../model/service/Playback.h"
#include "../view/IDisplayControl.h"
#include "../view/ISearchPanel.h"
#include <string>

class SearchController final : public IDisplayControl {
private:
    Catalog& catalog_;
    Playback& playback_;
    ISearchPanel& search_;

public:
    SearchController(Catalog& catalog, Playback& playback, ISearchPanel& search);
    void onSearch(const std::string& query) override;
    void onPick(const std::string& name) override;
};

#endif //SEARCH_CONTROLLER_H