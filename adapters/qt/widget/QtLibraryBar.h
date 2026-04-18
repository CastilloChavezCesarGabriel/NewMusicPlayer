#ifndef QT_LIBRARY_BAR_H
#define QT_LIBRARY_BAR_H

#include "../../../view/ILibraryControl.h"
#include "../../../view/IEnableable.h"
#include "IWidgetSetup.h"
#include <QWidget>
#include <QPushButton>

class QtLibraryBar final : public QWidget, public IWidgetSetup, public IEnableable {
    Q_OBJECT
private:
    QPushButton* add_button_;
    QPushButton* remove_button_;
    ILibraryControl& library_control_;

public:
    QtLibraryBar(ILibraryControl& library, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) override;

signals:
    void removeClicked();
};

#endif //QT_LIBRARY_BAR_H