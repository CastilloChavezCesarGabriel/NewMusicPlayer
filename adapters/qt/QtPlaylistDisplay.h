#ifndef QT_PLAYLIST_DISPLAY_H
#define QT_PLAYLIST_DISPLAY_H

#include "../../view/IPlaylistPanel.h"
#include "../../view/IPlaybackControl.h"
#include "../../view/ILibraryControl.h"
#include <QListView>
#include <QStringListModel>
#include <string>
#include <vector>

class QtPlaylistDisplay final : public QWidget, public IPlaylistPanel {
    Q_OBJECT
private:
    QListView* playlist_;
    QStringListModel* list_model_;

    void setup();

public:
    explicit QtPlaylistDisplay(QWidget* parent = nullptr);
    void refresh(const std::vector<std::string>& names) override;
    void highlight(int index) override;
    void remove();
    void wire(IPlaybackControl& playback, ILibraryControl& library);

signals:
    void selectRequested(int index);
    void removeRequested(int index);
};

#endif //QT_PLAYLIST_DISPLAY_H
