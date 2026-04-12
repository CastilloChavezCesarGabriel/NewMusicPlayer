#ifndef QT_ICON_PAINTER_H
#define QT_ICON_PAINTER_H

#include <QPushButton>
#include <string>

class QtIconPainter {
public:
    static void paint(QPushButton* button, const std::string& path);
};

#endif //QT_ICON_PAINTER_H