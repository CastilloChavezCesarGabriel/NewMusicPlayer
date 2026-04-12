#ifndef QT_PLAYLIST_DISPLAY_H
#define QT_PLAYLIST_DISPLAY_H

#include "../../../view/IPlaylistPanel.h"
#include "../../../view/IPlaybackControl.h"
#include "../../../view/ILibraryControl.h"
#include <QListView>
#include <QStringListModel>
#include <string>
#include <vector>

class QtPlaylistDisplay final : public QWidget, public IPlaylistPanel {
    Q_OBJECT
private:
    QListView* playlist_;
    QStringListModel* list_model_;
    IPlaybackControl& playback_;
    ILibraryControl& library_;

    void setup();

public:
    QtPlaylistDisplay(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent = nullptr);
    void refresh(const std::vector<std::string>& names) override;
    void highlight(int index) override;
    void remove();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

signals:
    void selectRequested(int index);
    void removeRequested(int index);
};

#endif //QT_PLAYLIST_DISPLAY_H