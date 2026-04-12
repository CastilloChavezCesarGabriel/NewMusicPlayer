#ifndef QT_TOOLBAR_H
#define QT_TOOLBAR_H

#include "../../../view/IToolbarDisplay.h"
#include "../../../view/IEnableable.h"
#include "../../../view/IPlaybackControl.h"
#include "../../../view/ILibraryControl.h"
#include <QWidget>
#include <QPushButton>
#include "IWidgetSetup.h"

class QtToolbar final : public QWidget, public IWidgetSetup, public IToolbarDisplay, public IEnableable {
    Q_OBJECT
private:
    QPushButton* add_button_;
    QPushButton* remove_button_;
    QPushButton* skip_button_;
    IPlaybackControl& playback_control_;
    ILibraryControl& library_control_;

public:
    QtToolbar(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) override;
    void reveal(bool visible) override;

signals:
    void addClicked();
    void removeClicked();
    void skipClicked();
};

#endif //QT_TOOLBAR_H