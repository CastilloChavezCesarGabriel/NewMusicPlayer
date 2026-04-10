#include "QtSearchField.h"

QtSearchField::QtSearchField(QWidget* parent) : QLineEdit(parent) {
    setPlaceholderText("Search...");

    connect(this, &QLineEdit::textChanged, this, [this](const QString& text) {
        emit searchRequested(text.toStdString());
    });
}