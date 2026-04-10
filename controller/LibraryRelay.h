#ifndef LIBRARY_RELAY_H
#define LIBRARY_RELAY_H

#include "../model/ILibraryListener.h"
#include "../model/service/Catalog.h"
#include "../view/IPlaylistPanel.h"
#include "../view/INotification.h"

class LibraryRelay final : public ILibraryListener {
private:
    Catalog& catalog_;
    IPlaylistPanel& panel_;
    INotification& notification_;

public:
    LibraryRelay(Catalog& catalog, IPlaylistPanel& panel, INotification& notification);
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //LIBRARY_RELAY_H