#ifndef LIBRARY_BUS_H
#define LIBRARY_BUS_H

#include "ILibraryListener.h"
#include <vector>
#include <functional>

class LibraryBus final : public ILibraryListener {
private:
    std::vector<ILibraryListener*> listeners_;
    void notify(const std::function<void(ILibraryListener*)>& action) const;

public:
    void add(ILibraryListener& listener);
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //LIBRARY_BUS_H
