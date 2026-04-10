#include "LibraryBus.h"

void LibraryBus::add(ILibraryListener& listener) {
    listeners_.push_back(&listener);
}

void LibraryBus::notify(const std::function<void(ILibraryListener*)>& action) const {
    for (auto* listener : listeners_) {
        action(listener);
    }
}

void LibraryBus::onChanged() {
    notify([](ILibraryListener* listener) { listener->onChanged(); });
}

void LibraryBus::onFeedback(const std::string& message, const bool success) {
    notify([&](ILibraryListener* listener) { listener->onFeedback(message, success); });
}