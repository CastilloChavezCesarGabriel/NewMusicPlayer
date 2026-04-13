#include "QtLibraryBar.h"
#include "../QtLayoutUtil.h"
#include <QHBoxLayout>

QtLibraryBar::QtLibraryBar(ILibraryControl& library, QWidget* parent)
    : QWidget(parent), library_control_(library) {
    setup();
    wire();
}

void QtLibraryBar::setup() {
    auto* layout = new QHBoxLayout(this);
    add_button_ = new QPushButton("Add Song", this);
    add_button_->setObjectName("add_button");
    remove_button_ = new QPushButton("Remove Song", this);
    remove_button_->setObjectName("remove_button");
    layout->addWidget(add_button_);
    layout->addWidget(remove_button_);
    QtLayoutUtil::center(layout);
}

void QtLibraryBar::wire() {
    connect(add_button_, &QPushButton::clicked, this, [this]() { library_control_.onAdd(); });
    connect(remove_button_, &QPushButton::clicked, this, &QtLibraryBar::removeClicked);
}

void QtLibraryBar::enable(const bool state) {
    add_button_->setEnabled(state);
    remove_button_->setEnabled(state);
}
