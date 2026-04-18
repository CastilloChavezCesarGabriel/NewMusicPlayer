#ifndef QT_SEARCH_OVERLAY_H
#define QT_SEARCH_OVERLAY_H

#include "../../../view/ISearchPanel.h"
#include "../../../view/IEnableable.h"
#include <QListWidget>
#include <QWidget>
#include <string>
#include <vector>

class QtSearchOverlay final : public QWidget, public ISearchPanel, public IEnableable {
    Q_OBJECT
private:
    QListWidget* results_;

    void setup();
    void align();
    void pick(const QListWidgetItem* item);

public:
    explicit QtSearchOverlay(QWidget* parent = nullptr);
    void suggest(const std::vector<std::string>& names) override;
    void dismiss() override;
    void enable(bool state) override;

signals:
    void selectRequested(const std::string& name);
};

#endif //QT_SEARCH_OVERLAY_H