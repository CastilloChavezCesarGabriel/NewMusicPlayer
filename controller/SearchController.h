#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "../model/service/TrackCatalog.h"
#include "../model/service/PlaybackService.h"
#include "../view/IDisplayControl.h"
#include "../view/ISearchPanel.h"
#include <string>

class SearchController final : public IDisplayControl {
private:
    TrackCatalog& catalog_;
    PlaybackService& playback_;
    ISearchPanel& search_;

public:
    SearchController(TrackCatalog& catalog, PlaybackService& playback, ISearchPanel& search);
    void onSearch(const std::string& query) override;
    void onPick(const std::string& name) override;
};

#endif //SEARCH_CONTROLLER_H