#ifndef QT_SEARCH_FIELD_CONNECTION_H
#define QT_SEARCH_FIELD_CONNECTION_H

#include "../widget/QtSearchField.h"
#include "../../../view/ISearchInput.h"
#include <QObject>

class QtSearchFieldConnection final : public QObject {
private:
    ISearchInput& display_control_;

public:
    QtSearchFieldConnection(QtSearchField& field, ISearchInput& display);

private slots:
    void relay(const std::string& query) const;
};

#endif