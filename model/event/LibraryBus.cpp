#include "LibraryBus.h"

void LibraryBus::onChanged() {
    broadcast([](ILibraryListener& listener) { listener.onChanged(); });
}

void LibraryBus::onFeedback(const std::string& message, const bool success) {
    broadcast([&](ILibraryListener& listener) { listener.onFeedback(message, success); });
}