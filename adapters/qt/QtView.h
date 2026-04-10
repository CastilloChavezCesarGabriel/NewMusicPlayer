#ifndef QT_VIEW_H
#define QT_VIEW_H

#include "../../view/ILibraryControl.h"
#include "../../view/IDisplayControl.h"
#include <QWidget>

class QLineEdit;
class QVBoxLayout;

class QtView final : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* layout_;
    QLineEdit* search_field_;
    ILibraryControl* library_control_ = nullptr;
    IDisplayControl* display_control_ = nullptr;

public:
    explicit QtView(QWidget* parent = nullptr);
    void place(QWidget& widget);
    void wire(ILibraryControl& library, IDisplayControl& display);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};

#endif //QT_VIEW_H
