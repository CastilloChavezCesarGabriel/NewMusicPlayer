#ifndef QT_ARRANGEMENT_PANEL_H
#define QT_ARRANGEMENT_PANEL_H

#include <QWidget>
#include <QPushButton>
#include "../../view/IArrangementControl.h"
#include "../../view/IRepeatDisplay.h"
#include "../../view/IEnableable.h"
#include "IWidgetSetup.h"

class QtArrangementPanel final : public QWidget, public IWidgetSetup, public IRepeatDisplay, public IEnableable {
    Q_OBJECT
private:
    IArrangementControl& arrangement_;
    QPushButton* shuffle_;
    QPushButton* repeat_;

    static void paint(QPushButton* button, const std::string& path);

public:
    explicit QtArrangementPanel(IArrangementControl& arrangement, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) override;
    void repeat(int mode) override;
};

#endif
