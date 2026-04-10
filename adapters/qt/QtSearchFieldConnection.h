#ifndef QT_SEARCH_FIELD_CONNECTION_H
#define QT_SEARCH_FIELD_CONNECTION_H

#include "QtSearchField.h"
#include "../../view/IDisplayControl.h"
#include <QObject>

class QtSearchFieldConnection final : public QObject {
private:
    IDisplayControl& display_control_;

public:
    QtSearchFieldConnection(QtSearchField& field, IDisplayControl& display);

private slots:
    void relay(const std::string& query) const;
};

#endif