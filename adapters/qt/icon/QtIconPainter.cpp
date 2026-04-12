#include "QtIconPainter.h"
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <filesystem>

void QtIconPainter::paint(QPushButton* button, const std::string& path) {
    const std::string resolved = std::filesystem::current_path().string() + path;
    QPixmap pixmap(QString::fromStdString(resolved));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.end();
    button->setIcon(QIcon(pixmap));
    button->setText("");
}