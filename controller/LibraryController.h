#ifndef LIBRARY_CONTROLLER_H
#define LIBRARY_CONTROLLER_H

#include "../model/service/LibraryEditor.h"
#include "../view/ILibraryControl.h"
#include "../view/IDialog.h"

class LibraryController final : public ILibraryControl {
private:
    LibraryEditor& library_;
    IDialog& dialog_;

public:
    LibraryController(LibraryEditor& library, IDialog& dialog);
    void onAdd() override;
    void onRemove(int index) override;
    void onDrop(const std::vector<std::string>& paths) override;
};

#endif //LIBRARY_CONTROLLER_H