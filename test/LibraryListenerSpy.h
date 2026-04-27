#ifndef LIBRARY_LISTENER_SPY_H
#define LIBRARY_LISTENER_SPY_H

#include "../model/event/ILibraryListener.h"
#include <string>
#include <vector>

class LibraryListenerSpy final : public ILibraryListener {
private:
    std::vector<std::string> feedbacks_;
    int changes_ = 0;

public:
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;

    void expectChange() const;
    void expectChanges(int expected) const;
    void expectNoChange() const;
    void expectFeedback(const std::string& message) const;
    void expectNoFeedback(const std::string& message) const;
};

#endif //LIBRARY_LISTENER_SPY_H