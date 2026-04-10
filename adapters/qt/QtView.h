#ifndef QT_VIEW_H
#define QT_VIEW_H

#include <QWidget>
#include "QVBoxLayout"

class QtView final : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* layout_;

public:
    explicit QtView(QWidget* parent = nullptr);
    void place(QWidget& widget);
    void attach(QWidget& widget);
};

#endif //QT_VIEW_H