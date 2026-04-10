#include "QtPlaylistDisplay.h"
#include "QtLayoutUtil.h"
#include <QVBoxLayout>

QtPlaylistDisplay::QtPlaylistDisplay(QWidget* parent) : QWidget(parent) {
    setup();
}

void QtPlaylistDisplay::setup() {
    auto* layout = new QVBoxLayout(this);
    QtLayoutUtil::flatten(layout);

    list_model_ = new QStringListModel(this);
    playlist_ = new QListView(this);
    playlist_->setModel(list_model_);

    layout->addWidget(playlist_);

    connect(playlist_, &QListView::doubleClicked, this, [this](const QModelIndex& index) {
        emit selectRequested(index.row());
    });
}

void QtPlaylistDisplay::refresh(const std::vector<std::string>& names) {
    QStringList list;
    for (const auto& name : names) {
        list.append(QString::fromStdString(name));
    }
    list_model_->setStringList(list);
}

void QtPlaylistDisplay::highlight(const int index) {
    if (index >= 0 && index < list_model_->rowCount()) {
        playlist_->setCurrentIndex(list_model_->index(index, 0));
    }
}

void QtPlaylistDisplay::remove() {
    const QModelIndex index = playlist_->currentIndex();
    if (index.isValid()) {
        emit removeRequested(index.row());
    }
}

void QtPlaylistDisplay::wire(IPlaybackControl& playback, ILibraryControl& library) {
    connect(this, &QtPlaylistDisplay::selectRequested, this, [&playback](const int index) {
        playback.onPlay(index);
    });

    connect(this, &QtPlaylistDisplay::removeRequested, this, [&library](const int index) {
        library.onRemove(index);
    });
}
