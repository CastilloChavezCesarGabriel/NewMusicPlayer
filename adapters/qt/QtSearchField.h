#ifndef QT_SEARCH_FIELD_H
#define QT_SEARCH_FIELD_H

#include <QLineEdit>
#include <string>

class QtSearchField final : public QLineEdit {
    Q_OBJECT
public:
    explicit QtSearchField(QWidget* parent = nullptr);

signals:
    void searchRequested(const std::string& query);
};

#endif //QT_SEARCH_FIELD_H