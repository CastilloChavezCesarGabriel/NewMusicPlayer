#include "QtView.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>

QtView::QtView(QWidget* parent) : QWidget(parent) {
    setObjectName("MainWindow");
    setWindowTitle("Music Player");
    setAcceptDrops(true);
    layout_ = new QVBoxLayout(this);
}

void QtView::place(QWidget& widget) {
    widget.setParent(this);
    layout_->addWidget(&widget);
}

void QtView::align(QWidget& left, QWidget& center, QWidget& right) {
    auto* row = new QWidget(this);
    auto* rowLayout = new QHBoxLayout(row);
    left.setParent(row);
    center.setParent(row);
    right.setParent(row);
    rowLayout->addWidget(&left);
    rowLayout->addWidget(&center);
    rowLayout->addWidget(&right);
    QtLayoutUtil::flatten(rowLayout);
    QtLayoutUtil::center(rowLayout);
    layout_->addWidget(row);
}

void QtView::attach(QWidget& widget) {
    widget.setParent(this);
}