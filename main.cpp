#include <filesystem>
#include "model/Playlist.h"
#include "model/MusicLibrary.h"
#include "model/Advertisement.h"
#include "model/PlaybackNotifier.h"
#include "model/RepeatMode.h"
#include "model/Song.h"
#include "model/Dice.h"
#include "model/service/Playback.h"
#include "model/service/Library.h"
#include "model/service/Setlist.h"
#include "model/service/Catalog.h"
#include "model/service/RepeatSwitch.h"
#include "adapters/qt/QtView.h"
#include "adapters/qt/QtStyler.h"
#include "controller/Controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    QtStyler::apply(app, base + "/resources/styles.qss");

    Dice dice;
    PlaybackNotifier notifier;

    MusicLibrary musicLibrary(base + "/resources/music");
    Playlist playlist(musicLibrary, notifier);
    for (const Song& song : musicLibrary.load()) {
        playlist.add(song);
    }
    playlist.shuffle();

    Advertisement advertisement(base + "/resources/announcements", dice, notifier);
    advertisement.load();

    RepeatMode repeatMode(playlist, notifier);

    Playback playback(playlist, advertisement, repeatMode);
    Library library(musicLibrary, playlist, notifier);
    Setlist setlist(playlist, notifier);
    Catalog catalog(playlist);
    RepeatSwitch repeatSwitch(repeatMode);

    QtView view;
    Controller controller(playback, library, setlist, catalog, repeatSwitch, view);
    notifier.add(controller);

    view.show();
    return app.exec();
}
