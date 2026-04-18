#include "QtSearchField.h"

QtSearchField::QtSearchField(QWidget* parent) : QLineEdit(parent) {
    setPlaceholderText("Search...");
    connect(this, &QLineEdit::textChanged, this, &QtSearchField::broadcast);
}

void QtSearchField::broadcast(const QString& text) {
    emit searchRequested(text.toStdString());
}