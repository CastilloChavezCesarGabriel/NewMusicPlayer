#ifndef QT_SORT_HEADER_H
#define QT_SORT_HEADER_H

#include "../../view/ISortDisplay.h"
#include <QPushButton>
#include <string>

class QtSortHeader final : public QWidget, public ISortDisplay {
    Q_OBJECT
private:
    QPushButton* header_;

public:
    explicit QtSortHeader(QWidget* parent = nullptr);
    void sort(const std::string& label) override;

signals:
    void clickRequested();
};

#endif //QT_SORT_HEADER_H