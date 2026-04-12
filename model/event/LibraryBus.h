#ifndef LIBRARY_BUS_H
#define LIBRARY_BUS_H

#include "Bus.h"
#include "ILibraryListener.h"

class LibraryBus final : public Bus<ILibraryListener>, public ILibraryListener {
public:
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //LIBRARY_BUS_H