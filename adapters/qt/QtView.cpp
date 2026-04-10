#include "QtView.h"
#include "QtDragDrop.h"
#include <QVBoxLayout>
#include <QLineEdit>

QtView::QtView(QWidget* parent) : QWidget(parent) {
    setObjectName("MainWindow");
    setWindowTitle("Music Player");
    setAcceptDrops(true);
    layout_ = new QVBoxLayout(this);
    search_field_ = new QLineEdit(this);
    search_field_->setPlaceholderText("Search...");
    layout_->addWidget(search_field_);
}

void QtView::place(QWidget& widget) {
    widget.setParent(this);
    layout_->addWidget(&widget);
}

void QtView::wire(ILibraryControl& library, IDisplayControl& display) {
    library_control_ = &library;
    display_control_ = &display;

    connect(search_field_, &QLineEdit::textChanged, this, [this](const QString& text) {
        display_control_->onSearch(text.toStdString());
    });
}

void QtView::dragEnterEvent(QDragEnterEvent* event) {
    QtDragDrop::accept(event);
}

void QtView::dropEvent(QDropEvent* event) {
    const std::vector<std::string> paths = QtDragDrop::extract(event);
    if (!paths.empty() && library_control_) library_control_->onDrop(paths);
}