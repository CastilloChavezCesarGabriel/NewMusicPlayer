#ifndef QT_SEARCH_OVERLAY_H
#define QT_SEARCH_OVERLAY_H

#include "../../view/ISearchPanel.h"
#include "../../view/IDisplayControl.h"
#include <QListWidget>
#include <QWidget>
#include <string>
#include <vector>

class QtSearchOverlay final : public QWidget, public ISearchPanel {
    Q_OBJECT
private:
    QListWidget* results_;

    void setup();
    void align();

public:
    explicit QtSearchOverlay(QWidget* parent = nullptr);
    void suggest(const std::vector<std::string>& names) override;
    void dismiss() override;
    void wire(IDisplayControl& display);

signals:
    void selectRequested(const std::string& name);
};

#endif //QT_SEARCH_OVERLAY_H
