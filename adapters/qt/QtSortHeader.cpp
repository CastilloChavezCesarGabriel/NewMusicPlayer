#include "QtSortHeader.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>
#include <QWidget>

QtSortHeader::QtSortHeader(QWidget* parent)
    : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);

    header_ = new QPushButton("Custom", this);
    header_->setObjectName("sort_header");
    header_->setFlat(true);
    header_->setCursor(Qt::PointingHandCursor);

    layout->addWidget(header_);
    QtLayoutUtil::flatten(layout);

    connect(header_, &QPushButton::clicked, this, &QtSortHeader::clickRequested);
}

void QtSortHeader::sort(const std::string& label) {
    header_->setText(QString::fromStdString(label));
}

void QtSortHeader::wire(IArrangementControl& arrangement) {
    connect(this, &QtSortHeader::clickRequested, this, [&arrangement]() {
        arrangement.onSort();
    });
}
