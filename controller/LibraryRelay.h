#ifndef LIBRARY_RELAY_H
#define LIBRARY_RELAY_H

#include "../model/event/ILibraryListener.h"
#include "../model/service/TrackCatalog.h"
#include "../view/IPlaylistPanel.h"
#include "../view/INotification.h"

class LibraryRelay final : public ILibraryListener {
private:
    TrackCatalog& catalog_;
    IPlaylistPanel& panel_;
    INotification& notification_;

public:
    LibraryRelay(TrackCatalog& catalog, IPlaylistPanel& panel, INotification& notification);
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //LIBRARY_RELAY_H