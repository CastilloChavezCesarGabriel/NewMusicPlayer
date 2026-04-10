#include "QtView.h"

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

void QtView::attach(QWidget& widget) {
    widget.setParent(this);
}