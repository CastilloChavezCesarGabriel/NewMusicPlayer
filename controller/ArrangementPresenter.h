#ifndef ARRANGEMENT_PRESENTER_H
#define ARRANGEMENT_PRESENTER_H

#include "../model/event/ILibraryListener.h"
#include "PlaybackModeController.h"

class ArrangementPresenter final : public ILibraryListener {
private:
    PlaybackModeController& arrangement_;

public:
    explicit ArrangementPresenter(PlaybackModeController& arrangement);
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //ARRANGEMENT_PRESENTER_H
