#ifndef ARRANGEMENT_RELAY_H
#define ARRANGEMENT_RELAY_H

#include "../model/event/ILibraryListener.h"
#include "../view/IRefreshable.h"

class ArrangementRelay final : public ILibraryListener {
private:
    IRefreshable& arrangement_;

public:
    explicit ArrangementRelay(IRefreshable& arrangement);
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //ARRANGEMENT_RELAY_H