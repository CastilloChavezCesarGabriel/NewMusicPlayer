#ifndef ARRANGEMENT_RELAY_H
#define ARRANGEMENT_RELAY_H

#include "../model/event/ILibraryListener.h"
#include "ArrangementController.h"

class ArrangementRelay final : public ILibraryListener {
private:
    ArrangementController& arrangement_;

public:
    explicit ArrangementRelay(ArrangementController& arrangement);
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //ARRANGEMENT_RELAY_H
