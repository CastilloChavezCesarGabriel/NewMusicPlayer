#include "QtView.h"
#include "QtViewFactory.h"
#include "QtSearchOverlay.h"
#include "QtDragDrop.h"
#include <QVBoxLayout>
#include "QtVolumePanel.h"
#include "QtSortHeader.h"

QtView::QtView(QWidget* parent) : QWidget(parent) {
    setObjectName("MainWindow");
    audio_ = new QtAudioEngine(this);

    QObject::connect(audio_, &QtAudioEngine::revealRequested, this, [this]() {
        toolbar_->reveal(true);
    });

    QObject::connect(audio_, &QtAudioEngine::toggleRequested, this, [this](const bool playing) {
        playback_->toggle(playing);
    });

    setup();
    setAcceptDrops(true);
}

void QtView::setup() {
    setWindowTitle("Music Player");

    auto* main = new QVBoxLayout(this);
    auto* search = new QLineEdit(this);
    search->setPlaceholderText("Search...");
    sort_header_ = new QtSortHeader(this);
    display_ = new QtPlaylistDisplay(this);
    search_overlay_ = new QtSearchOverlay(this);
    notification_ = QtViewFactory::createNotification(this);
    dialog_ = QtViewFactory::createDialog(this);

    main->addWidget(search);
    main->addWidget(sort_header_);
    main->addWidget(display_);
    main->addWidget(audio_);

    QObject::connect(sort_header_, &QtSortHeader::clickRequested, this, [this]() {
        arrangement_control_->onSort();
    });

    link(search);
}

void QtView::link(QLineEdit* search) {
    QObject::connect(display_, &QtPlaylistDisplay::selectRequested, this, [this](const int index) {
        playback_control_->onPlay(index);
    });

    QObject::connect(search, &QLineEdit::textChanged, this, [this](const QString& text) {
        display_control_->onSearch(text.toStdString());
    });

    QObject::connect(search_overlay_, &QtSearchOverlay::selectRequested, this, [this, search](const std::string& name) {
        display_control_->onPick(name);
        search->clear();
    });
}

void QtView::wire(IPlaybackControl& playback, IArrangementControl& arrangement,
                  ILibraryControl& library, IDisplayControl& display) {
    playback_control_ = &playback;
    arrangement_control_ = &arrangement;
    library_control_ = &library;
    display_control_ = &display;

    QObject::connect(audio_, &QtAudioEngine::endRequested, this, [this]() {
        playback_control_->onEnd();
    });

    auto* main = layout();
    playback_ = QtViewFactory::createPlayback(*playback_control_, *arrangement_control_, this);
    auto* volume = QtViewFactory::createVolume(*playback_control_, this);
    toolbar_ = QtViewFactory::createToolbar(this);

    main->addWidget(playback_);
    main->addWidget(volume);
    main->addWidget(toolbar_);

    bind();
}

void QtView::bind() {
    QObject::connect(toolbar_, &QtToolbar::addClicked, this, [this]() {
        library_control_->onAdd();
    });
    QObject::connect(toolbar_, &QtToolbar::removeClicked, display_, &QtPlaylistDisplay::remove);
    QObject::connect(display_, &QtPlaylistDisplay::removeRequested, this, [this](const int index) {
        library_control_->onRemove(index);
    });
    QObject::connect(toolbar_, &QtToolbar::skipClicked, this, [this]() {
        playback_control_->onSkip();
    });
}

void QtView::refresh(const std::vector<std::string>& names) {
    display_->refresh(names);
}

void QtView::highlight(const int index) {
    display_->highlight(index);
}

void QtView::suggest(const std::vector<std::string>& names) {
    search_overlay_->display(names);
}

void QtView::dismiss() {
    search_overlay_->clear();
}

void QtView::enable(const bool state) {
    playback_->enable(state);
    toolbar_->enable(state);
    audio_->enable(state);
}

void QtView::schedule(const int delay) {
    audio_->schedule(delay);
}

void QtView::cancel() {
    audio_->cancel();
}

void QtView::repeat(const int mode) {
    playback_->repeat(mode);
}

void QtView::sort(const std::string& label) {
    sort_header_->display(label);
}

void QtView::reveal(const bool visible) {
    toolbar_->reveal(visible);
}

void QtView::notify(const std::string& message, const bool success) {
    notification_->notify(message, success);
}

bool QtView::confirm(const std::string& message) {
    return dialog_->confirm(message);
}

std::string QtView::browse() {
    return dialog_->browse();
}

void QtView::play(const std::string& path) {
    audio_->play(path);
}

void QtView::resume() {
    audio_->resume();
}

void QtView::pause() {
    audio_->pause();
}

void QtView::stop() {
    audio_->stop();
}

void QtView::adjust(const int volume) {
    audio_->adjust(volume / 100.0);
}

void QtView::dragEnterEvent(QDragEnterEvent* event) {
    QtDragDrop::accept(event);
}

void QtView::dropEvent(QDropEvent* event) {
    const std::vector<std::string> paths = QtDragDrop::extract(event);
    if (!paths.empty()) library_control_->onDrop(paths);
}
