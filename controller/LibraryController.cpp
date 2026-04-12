#include "LibraryController.h"

LibraryController::LibraryController(LibraryService& library, IDialog& dialog)
    : library_(library), dialog_(dialog) {}

void LibraryController::onAdd() {
    const std::string path = dialog_.browse();
    if (!path.empty()) {
        library_.insert(path);
    }
}

void LibraryController::onRemove(const int index) {
    if (dialog_.confirm("Are you sure you wanna delete this song?")) {
        library_.remove(index);
    }
}

void LibraryController::onDrop(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        library_.insert(path);
    }
}