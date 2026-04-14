#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "../model/service/ISearchProvider.h"
#include "../model/service/PlaybackService.h"
#include "../view/IDisplayControl.h"
#include "../view/ISearchPanel.h"
#include <string>

class SearchController final : public IDisplayControl {
private:
    ISearchProvider& provider_;
    PlaybackService& playback_;
    ISearchPanel& search_;

public:
    SearchController(ISearchProvider& provider, PlaybackService& playback, ISearchPanel& search);
    void onSearch(const std::string& query) override;
    void onPick(const std::string& name) override;
};

#endif //SEARCH_CONTROLLER_H