#ifndef ARRANGEMENT_PRESENTER_H
#define ARRANGEMENT_PRESENTER_H

#include "../model/event/ILibraryListener.h"
#include "OrderingController.h"

class ArrangementPresenter final : public ILibraryListener {
private:
    OrderingController& ordering_;

public:
    explicit ArrangementPresenter(OrderingController& ordering);
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //ARRANGEMENT_PRESENTER_H