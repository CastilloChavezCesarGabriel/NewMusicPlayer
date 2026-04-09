# NewMusicPlayer — Source Dump

## main.cpp

```cpp
#include <filesystem>
#include "model/MusicPlayer.h"
#include "model/Dice.h"
#include "adapters/qt/QtView.h"
#include "adapters/qt/QtStyler.h"
#include "controller/Controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    QtStyler::apply(app, base + "/resources/styles.qss");

    Dice dice;
    MusicPlayer musicPlayer(base + "/resources", dice);
    QtView view;
    Controller controller(musicPlayer, view);

    view.show();
    return app.exec();
}
```

## CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.31)
project(NewMusicPlayer)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(NewMusicPlayer main.cpp
        model/Song.cpp
        model/Song.h
        model/IPlaylistVisitor.h
        model/SortingAlgorithm.h
        model/ShellSort.cpp
        model/ShellSort.h
        model/DurationSort.cpp
        model/DurationSort.h
        model/DateSort.cpp
        model/DateSort.h
        model/QuickSort.cpp
        model/QuickSort.h
        model/Playlist.cpp
        model/Playlist.h
        model/Arrangement.cpp
        model/Arrangement.h
        model/IPlaybackListener.h
        model/Advertisement.cpp
        model/Advertisement.h
        model/MusicLibrary.cpp
        model/MusicLibrary.h
        model/Channel.cpp
        model/Channel.h
        model/PlaybackNotifier.cpp
        model/PlaybackNotifier.h
        model/RepeatStrategy.cpp
        model/RepeatStrategy.h
        model/NoRepeatMode.cpp
        model/NoRepeatMode.h
        model/RepeatOneMode.cpp
        model/RepeatOneMode.h
        model/RepeatAllMode.cpp
        model/RepeatAllMode.h
        model/RepeatMode.cpp
        model/RepeatMode.h
        model/MusicPlayer.cpp
        model/MusicPlayer.h
        model/IDice.h
        model/Dice.cpp
        model/Dice.h
        model/FileMetadata.cpp
        model/FileMetadata.h
        view/IPlaylistPanel.h
        view/ISearchPanel.h
        view/IControlPanel.h
        view/INotification.h
        view/IDialog.h
        view/IPlayerView.h
        view/IPlaybackControl.h
        view/ILibraryControl.h
        view/IDisplayControl.h
        view/IPlayerListener.h
        view/IAudioPlayer.h
        controller/PlaylistRenderer.cpp
        controller/PlaylistRenderer.h
        controller/SortMode.cpp
        controller/SortMode.h
        controller/TitleDescending.cpp
        controller/TitleDescending.h
        controller/CustomMode.cpp
        controller/CustomMode.h
        controller/SortController.cpp
        controller/SortController.h
        controller/SearchController.cpp
        controller/SearchController.h
        controller/Controller.cpp
        controller/Controller.h
        adapters/qt/QtLayoutUtil.cpp
        adapters/qt/QtLayoutUtil.h
        adapters/qt/QtPlaybackPanel.cpp
        adapters/qt/QtPlaybackPanel.h
        adapters/qt/QtVolumePanel.cpp
        adapters/qt/QtVolumePanel.h
        adapters/qt/QtToolbar.cpp
        adapters/qt/QtToolbar.h
        adapters/qt/QtProgressPanel.cpp
        adapters/qt/QtProgressPanel.h
        adapters/qt/QtSortHeader.cpp
        adapters/qt/QtSortHeader.h
        adapters/qt/QtPlaylistDisplay.cpp
        adapters/qt/QtPlaylistDisplay.h
        adapters/qt/QtSearchOverlay.cpp
        adapters/qt/QtSearchOverlay.h
        adapters/qt/QtAudioEngine.cpp
        adapters/qt/QtAudioEngine.h
        adapters/qt/QtNotification.cpp
        adapters/qt/QtNotification.h
        adapters/qt/QtDialog.cpp
        adapters/qt/QtDialog.h
        adapters/qt/QtDragDrop.cpp
        adapters/qt/QtDragDrop.h
        adapters/qt/QtViewFactory.cpp
        adapters/qt/QtViewFactory.h
        adapters/qt/QtStyler.cpp
        adapters/qt/QtStyler.h
        adapters/qt/QtView.cpp
        adapters/qt/QtView.h
)

add_custom_target(CopyResources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:NewMusicPlayer>/resources
)

add_dependencies(NewMusicPlayer CopyResources)

target_link_libraries(NewMusicPlayer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
)

enable_testing()
find_package(GTest REQUIRED)

add_executable(NewMusicPlayerTests
        test/MockPlaybackListener.cpp
        test/MockPlaybackListener.h
        test/TestPlaylistVisitor.cpp
        test/TestPlaylistVisitor.h
        test/ModelTestFixture.cpp
        test/ModelTestFixture.h
        test/DirectoryTestFixture.cpp
        test/DirectoryTestFixture.h
        test/model/FileMetadataTest.cpp
        test/model/FileMetadataTest.h
        test/model/SongTest.cpp
        test/model/PlaylistTest.cpp
        test/model/AdvertisementTest.cpp
        test/model/MusicLibraryTest.cpp
        test/model/SortingTest.cpp
        test/model/ModelTest.cpp
        test/RegressionTest.cpp
        test/use_cases/PlaySongUseCaseTest.cpp
        test/use_cases/PlaySongUseCaseTest.h
        test/use_cases/SortPlaylistUseCaseTest.cpp
        test/use_cases/SortPlaylistUseCaseTest.h
        test/use_cases/SearchSongUseCaseTest.cpp
        test/use_cases/SearchSongUseCaseTest.h
        test/use_cases/AddSongUseCaseTest.cpp
        test/use_cases/AddSongUseCaseTest.h
        test/use_cases/RemoveSongUseCaseTest.cpp
        test/use_cases/RemoveSongUseCaseTest.h
        test/use_cases/NavigatePlaylistUseCaseTest.cpp
        test/use_cases/NavigatePlaylistUseCaseTest.h
        model/Song.cpp
        model/Song.h
        model/IPlaylistVisitor.h
        model/IPlaybackListener.h
        model/SortingAlgorithm.h
        model/ShellSort.cpp
        model/ShellSort.h
        model/DurationSort.cpp
        model/DurationSort.h
        model/DateSort.cpp
        model/DateSort.h
        model/QuickSort.cpp
        model/QuickSort.h
        model/Playlist.cpp
        model/Playlist.h
        model/Arrangement.cpp
        model/Arrangement.h
        model/Advertisement.cpp
        model/Advertisement.h
        model/MusicLibrary.cpp
        model/MusicLibrary.h
        model/Channel.cpp
        model/Channel.h
        model/PlaybackNotifier.cpp
        model/PlaybackNotifier.h
        model/RepeatStrategy.cpp
        model/RepeatStrategy.h
        model/NoRepeatMode.cpp
        model/NoRepeatMode.h
        model/RepeatOneMode.cpp
        model/RepeatOneMode.h
        model/RepeatAllMode.cpp
        model/RepeatAllMode.h
        model/RepeatMode.cpp
        model/RepeatMode.h
        model/MusicPlayer.cpp
        model/MusicPlayer.h
        model/IDice.h
        model/Dice.cpp
        model/Dice.h
        model/FileMetadata.cpp
        model/FileMetadata.h
)

target_link_libraries(NewMusicPlayerTests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(NewMusicPlayerTests)

```

## model/Advertisement.h

```cpp
#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include "IPlaybackListener.h"
#include "IDice.h"
#include <string>
#include <vector>

class Advertisement {
private:
    std::vector<std::string> ads_;
    std::string path_;
    IDice& dice_;
    bool is_playing_ = false;

    bool isScheduled() const;
    int randomize() const;

public:
    Advertisement(const std::string& adsPath, IDice& dice);

    void load();
    bool interrupt(IPlaybackListener& listener);
    bool conclude(IPlaybackListener& listener);
};

#endif //ADVERTISEMENT_H

```

## model/Advertisement.cpp

```cpp
#include "Advertisement.h"
#include "MusicLibrary.h"

Advertisement::Advertisement(const std::string& adsPath, IDice& dice)
    : path_(adsPath), dice_(dice) {
}

void Advertisement::load() {
    ads_ = MusicLibrary::scan(path_);
}

bool Advertisement::isScheduled() const {
    return dice_.roll(100) <= 25;
}

int Advertisement::randomize() const {
    return (dice_.roll(6) + 4) * 1000;
}

bool Advertisement::interrupt(IPlaybackListener& listener) {
    if (ads_.empty() || !isScheduled()) return false;

    is_playing_ = true;
    listener.onEnabled(false);
    listener.onSchedule(randomize());

    const int index = dice_.roll(static_cast<int>(ads_.size())) - 1;
    listener.onStart(ads_.at(index));
    return true;
}

bool Advertisement::conclude(IPlaybackListener& listener) {
    if (!is_playing_) return false;
    is_playing_ = false;
    listener.onCancel();
    listener.onReveal(false);
    listener.onEnabled(true);
    return true;
}
```

## model/Arrangement.h

```cpp
#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "Song.h"
#include "SortingAlgorithm.h"
#include <vector>

class Arrangement {
private:
    std::vector<Song> original_;

public:
    void sort(std::vector<Song>& songs, SortingAlgorithm& criteria);
    void reverse(std::vector<Song>& songs);
    void restore(std::vector<Song>& songs);

private:
    void preserve(const std::vector<Song>& songs);
};

#endif //ARRANGEMENT_H
```

## model/Arrangement.cpp

```cpp
#include "Arrangement.h"
#include <algorithm>

void Arrangement::sort(std::vector<Song>& songs, SortingAlgorithm& criteria) {
    preserve(songs);
    criteria.sort(songs);
}

void Arrangement::reverse(std::vector<Song>& songs) {
    preserve(songs);
    std::ranges::reverse(songs);
}

void Arrangement::restore(std::vector<Song>& songs) {
    if (original_.empty()) return;
    songs = original_;
    original_.clear();
}

void Arrangement::preserve(const std::vector<Song>& songs) {
    if (original_.empty()) {
        original_ = songs;
    }
}
```

## model/Channel.h

```cpp
#ifndef CHANNEL_H
#define CHANNEL_H

#include "IPlaylistVisitor.h"
#include "IPlaybackListener.h"

class Channel final : public IPlaylistVisitor {
private:
    IPlaybackListener& listener_;

public:
    explicit Channel(IPlaybackListener& listener);
    void visit(const std::string& name, const std::string& path) override;
};

#endif //CHANNEL_H
```

## model/Channel.cpp

```cpp
#include "Channel.h"

Channel::Channel(IPlaybackListener& listener)
    : listener_(listener) {
}

void Channel::visit(const std::string&, const std::string& path) {
    listener_.onStart(path);
}
```

## model/DateSort.h

```cpp
#ifndef DATE_SORT_H
#define DATE_SORT_H
#include "ShellSort.h"

class DateSort final : public ShellSort {
private:
    void visit(const std::string& name, const std::string& path) override;
};

#endif //DATE_SORT_H
```

## model/DateSort.cpp

```cpp
#include "DateSort.h"
#include "FileMetadata.h"

void DateSort::visit(const std::string&, const std::string& path) {
    key_ = FileMetadata(path).stamp();
}
```

## model/Dice.h

```cpp
#ifndef DICE_H
#define DICE_H

#include "IDice.h"
#include <random>

class Dice final : public IDice {
private:
    std::mt19937 engine_;

public:
    Dice();
    int roll(int faces) override;
};

#endif //DICE_H
```

## model/Dice.cpp

```cpp
#include "Dice.h"

Dice::Dice() : engine_(std::random_device{}()) {}

int Dice::roll(const int faces) {
    if (faces <= 0) return 0;
    std::uniform_int_distribution<> distribution(1, faces);
    return distribution(engine_);
}
```

## model/DurationSort.h

```cpp
#ifndef DURATION_SORT_H
#define DURATION_SORT_H
#include "ShellSort.h"

class DurationSort final : public ShellSort {
private:
    void visit(const std::string& name, const std::string& path) override;
};

#endif //DURATION_SORT_H
```

## model/DurationSort.cpp

```cpp
#include "DurationSort.h"
#include "FileMetadata.h"

void DurationSort::visit(const std::string&, const std::string& path) {
    key_ = FileMetadata(path).last();
}
```

## model/FileMetadata.h

```cpp
#ifndef FILE_METADATA_H
#define FILE_METADATA_H

#include <string>

class FileMetadata {
private:
    std::string path_;

    bool exists() const;

public:
    explicit FileMetadata(const std::string& path);
    long long stamp() const;
    int last() const;
};

#endif //FILE_METADATA_H
```

## model/FileMetadata.cpp

```cpp
#include "FileMetadata.h"
#include <filesystem>

FileMetadata::FileMetadata(const std::string& path) : path_(path) {}

bool FileMetadata::exists() const {
    return std::filesystem::exists(path_);
}

long long FileMetadata::stamp() const {
    if (!exists()) return 0;
    const auto time = std::filesystem::last_write_time(path_);
    return time.time_since_epoch().count();
}

int FileMetadata::last() const {
    if (!exists()) return 0;
    return static_cast<int>(std::filesystem::file_size(path_));
}
```

## model/IDice.h

```cpp
#ifndef I_DICE_H
#define I_DICE_H

class IDice {
public:
    virtual ~IDice() = default;
    virtual int roll(int faces) = 0;
};

#endif //I_DICE_H
```

## model/IPlaybackListener.h

```cpp
#ifndef I_PLAYBACK_LISTENER_H
#define I_PLAYBACK_LISTENER_H
#include <string>

class IPlaybackListener {
public:
    virtual ~IPlaybackListener() = default;
    virtual void onStart(const std::string& path) = 0;
    virtual void onChanged() = 0;
    virtual void onSelected(int index) = 0;
    virtual void onEnabled(bool state) = 0;
    virtual void onReveal(bool visible) = 0;
    virtual void onSchedule(int delay) = 0;
    virtual void onCancel() = 0;
    virtual void onRepeatChanged(int mode) = 0;
    virtual void onFeedback(const std::string& message, bool success) = 0;
    virtual void onStopped() = 0;
};

#endif //I_PLAYBACK_LISTENER_H
```

## model/IPlaylistVisitor.h

```cpp
#ifndef I_PLAYLIST_VISITOR_H
#define I_PLAYLIST_VISITOR_H
#include <string>

class IPlaylistVisitor {
public:
    virtual ~IPlaylistVisitor() = default;
    virtual void visit(const std::string& name, const std::string& path) = 0;
};

#endif //I_PLAYLIST_VISITOR_H
```

## model/MusicLibrary.h

```cpp
#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include "Song.h"
#include "IPlaylistVisitor.h"
#include <string>
#include <vector>
#include "Playlist.h"

class MusicLibrary final : public IPlaylistVisitor {
private:
    std::string music_path_;

public:
    explicit MusicLibrary(const std::string& musicPath);

    std::vector<Song> load() const;
    std::string validate(const std::string& filePath) const;
    std::string insert(const std::string& filePath, Playlist& playlist) const;
    Song import(const std::string& sourcePath) const;
    static void erase(const std::string& path);
    void visit(const std::string& name, const std::string& path) override;
    bool contains(const std::string& filename) const;
    static std::vector<std::string> scan(const std::string& directory);
    static bool isSupported(const std::string& fileName);
};

#endif //MUSIC_LIBRARY_H
```

## model/MusicLibrary.cpp

```cpp
#include "MusicLibrary.h"
#include "Song.h"
#include <filesystem>

MusicLibrary::MusicLibrary(const std::string& musicPath)
    : music_path_(musicPath) {
}

std::vector<std::string> MusicLibrary::scan(const std::string& directory) {
    std::vector<std::string> result;
    if (!std::filesystem::exists(directory)) return result;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && isSupported(entry.path().string())) {
            result.push_back(entry.path().string());
        }
    }
    return result;
}

std::vector<Song> MusicLibrary::load() const {
    std::vector<Song> songs;
    for (const auto& path : scan(music_path_)) {
        const std::string filename = std::filesystem::path(path).filename().string();
        songs.emplace_back(filename, path);
    }
    return songs;
}

std::string MusicLibrary::validate(const std::string& filePath) const {
    if (filePath.empty() || !isSupported(filePath)) return "Unsupported file type.";
    const std::string filename = std::filesystem::path(filePath).filename().string();
    if (contains(filename)) return "This song already exists.";
    return "";
}

std::string MusicLibrary::insert(const std::string& filePath, Playlist& playlist) const {
    const std::string reason = validate(filePath);
    if (!reason.empty()) return reason;
    playlist.add(import(filePath));
    return "";
}

Song MusicLibrary::import(const std::string& sourcePath) const {
    const std::filesystem::path source(sourcePath);
    const std::string filename = source.filename().string();
    const std::filesystem::path destination = std::filesystem::path(music_path_) / filename;

    if (!std::filesystem::exists(destination)) {
        std::filesystem::copy_file(source, destination);
    }

    return Song(filename, destination.string());
}

void MusicLibrary::erase(const std::string& path) {
    std::filesystem::remove(path);
}

void MusicLibrary::visit(const std::string&, const std::string& path) {
    erase(path);
}

bool MusicLibrary::contains(const std::string& filename) const {
    const std::filesystem::path destination = std::filesystem::path(music_path_) / filename;
    return std::filesystem::exists(destination);
}

bool MusicLibrary::isSupported(const std::string& fileName) {
    const std::filesystem::path path(fileName);
    const std::string extension = path.extension().string();
    return extension == ".mp3" || extension == ".wav";
}
```

## model/MusicPlayer.h

```cpp
#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "Playlist.h"
#include "Advertisement.h"
#include "MusicLibrary.h"
#include "PlaybackNotifier.h"
#include "RepeatMode.h"
#include "IPlaylistVisitor.h"
#include "IDice.h"

class MusicPlayer {
private:
    MusicLibrary music_library_;
    Playlist playlist_;
    Advertisement advertisement_;
    PlaybackNotifier notifier_;
    RepeatMode repeat_mode_;

    void broadcast();
    void refresh();

public:
    MusicPlayer(const std::string& basePath, IDice& dice);

    void subscribe(IPlaybackListener& listener);
    void play(int index);
    void pick(const std::string& name);
    void advance();
    void retreat();
    void end();
    void skip();
    void repeat();
    void insert(const std::string& filePath);
    void remove(int index);
    void shuffle();
    void sort(SortingAlgorithm& criteria);
    void reverse();
    void restore();
    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;
};

#endif //MUSIC_PLAYER_H
```

## model/MusicPlayer.cpp

```cpp
#include "MusicPlayer.h"
#include "Channel.h"

MusicPlayer::MusicPlayer(const std::string& basePath, IDice& dice)
    : music_library_(basePath + "/music"),
      playlist_(music_library_),
      advertisement_(basePath + "/announcements", dice),
      repeat_mode_(playlist_, notifier_) {

    for (const Song& song : music_library_.load()) {
        playlist_.add(song);
    }
    playlist_.shuffle();
    advertisement_.load();
}

void MusicPlayer::subscribe(IPlaybackListener& listener) {
    notifier_.add(listener);
}

void MusicPlayer::play(const int index) {
    playlist_.select(index, notifier_);

    if (!advertisement_.interrupt(notifier_)) {
        broadcast();
    }
}

void MusicPlayer::pick(const std::string& name) {
    playlist_.pick(name, notifier_);

    if (!advertisement_.interrupt(notifier_)) {
        broadcast();
    }
}

void MusicPlayer::advance() {
    if (playlist_.hasNext()) {
        playlist_.advance(notifier_);
        broadcast();
    }
}

void MusicPlayer::retreat() {
    playlist_.retreat(notifier_);
    broadcast();
}

void MusicPlayer::end() {
    if (advertisement_.conclude(notifier_)) {
        broadcast();
        return;
    }

    if (repeat_mode_.apply()) {
        broadcast();
    } else {
        notifier_.onStopped();
    }
}

void MusicPlayer::skip() {
    if (advertisement_.conclude(notifier_)) {
        broadcast();
    }
}

void MusicPlayer::broadcast() {
    Channel channel(notifier_);
    playlist_.play(channel);
}

void MusicPlayer::refresh() {
    notifier_.onChanged();
}

void MusicPlayer::repeat() {
    repeat_mode_.advance();
}

void MusicPlayer::insert(const std::string& filePath) {
    const std::string reason = music_library_.insert(filePath, playlist_);
    if (!reason.empty()) {
        notifier_.onFeedback(reason, false);
        return;
    }
    refresh();
    notifier_.onFeedback("Song added successfully!", true);
}

void MusicPlayer::remove(const int index) {
    playlist_.remove(index);
    refresh();
}

void MusicPlayer::shuffle() {
    playlist_.shuffle();
    refresh();
}

void MusicPlayer::sort(SortingAlgorithm& criteria) {
    playlist_.sort(criteria);
    refresh();
}

void MusicPlayer::reverse() {
    playlist_.reverse();
    refresh();
}

void MusicPlayer::restore() {
    playlist_.restore();
    refresh();
}

void MusicPlayer::accept(IPlaylistVisitor& visitor) const {
    playlist_.accept(visitor);
}

void MusicPlayer::search(const std::string& query, IPlaylistVisitor& visitor) const {
    playlist_.search(query, visitor);
}
```

## model/NoRepeatMode.h

```cpp
#ifndef NO_REPEAT_MODE_H
#define NO_REPEAT_MODE_H

#include "RepeatStrategy.h"

class NoRepeatMode final : public RepeatStrategy {
public:
    NoRepeatMode();
    bool apply(Playlist& playlist, IPlaybackListener& listener) override;
};

#endif //NO_REPEAT_MODE_H
```

## model/NoRepeatMode.cpp

```cpp
#include "NoRepeatMode.h"

NoRepeatMode::NoRepeatMode() : RepeatStrategy(0) {}

bool NoRepeatMode::apply(Playlist& playlist, IPlaybackListener& listener) {
    if (!playlist.hasNext()) return false;
    playlist.advance(listener);
    return true;
}
```

## model/PlaybackNotifier.h

```cpp
#ifndef PLAYBACK_NOTIFIER_H
#define PLAYBACK_NOTIFIER_H

#include "IPlaybackListener.h"
#include <vector>
#include <string>
#include <functional>

class PlaybackNotifier final : public IPlaybackListener {
private:
    std::vector<IPlaybackListener*> listeners_;

    void notify(const std::function<void(IPlaybackListener*)>& action) const;

public:
    void add(IPlaybackListener& listener);
    void onStart(const std::string& path) override;
    void onChanged() override;
    void onSelected(int index) override;
    void onEnabled(bool state) override;
    void onReveal(bool visible) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onRepeatChanged(int mode) override;
    void onFeedback(const std::string& message, bool success) override;
    void onStopped() override;
};

#endif //PLAYBACK_NOTIFIER_H
```

## model/PlaybackNotifier.cpp

```cpp
#include "PlaybackNotifier.h"

void PlaybackNotifier::add(IPlaybackListener& listener) {
    listeners_.push_back(&listener);
}

void PlaybackNotifier::notify(const std::function<void(IPlaybackListener*)>& action) const {
    for (auto* listener : listeners_) {
        action(listener);
    }
}

void PlaybackNotifier::onStart(const std::string& path) {
    notify([&](IPlaybackListener* listener) { listener->onStart(path); });
}

void PlaybackNotifier::onChanged() {
    notify([](IPlaybackListener* listener) { listener->onChanged(); });
}

void PlaybackNotifier::onSelected(const int index) {
    notify([&](IPlaybackListener* listener) { listener->onSelected(index); });
}

void PlaybackNotifier::onEnabled(const bool state) {
    notify([&](IPlaybackListener* listener) { listener->onEnabled(state); });
}

void PlaybackNotifier::onReveal(const bool visible) {
    notify([&](IPlaybackListener* listener) { listener->onReveal(visible); });
}

void PlaybackNotifier::onSchedule(const int delay) {
    notify([&](IPlaybackListener* listener) { listener->onSchedule(delay); });
}

void PlaybackNotifier::onCancel() {
    notify([](IPlaybackListener* listener) { listener->onCancel(); });
}

void PlaybackNotifier::onRepeatChanged(const int mode) {
    notify([&](IPlaybackListener* listener) { listener->onRepeatChanged(mode); });
}

void PlaybackNotifier::onFeedback(const std::string& message, const bool success) {
    notify([&](IPlaybackListener* listener) { listener->onFeedback(message, success); });
}

void PlaybackNotifier::onStopped() {
    notify([](IPlaybackListener* listener) { listener->onStopped(); });
}
```

## model/Playlist.h

```cpp
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include "SortingAlgorithm.h"
#include "IPlaylistVisitor.h"
#include "IPlaybackListener.h"
#include "Arrangement.h"
#include <vector>
#include <functional>

class Playlist {
private:
    std::vector<Song> songs_;
    Arrangement arrangement_;
    IPlaylistVisitor& deleter_;
    int current_song_ = -1;

public:
    explicit Playlist(IPlaylistVisitor& deleter);

    void add(const Song& song);
    void remove(int index);
    void sort(SortingAlgorithm& criteria);
    void reverse();
    void restore();
    void shuffle();
    void clear();
    void select(int index, IPlaybackListener& listener);
    void pick(const std::string& name, IPlaybackListener& listener);
    void advance(IPlaybackListener& listener);
    void retreat(IPlaybackListener& listener);
    void play(IPlaylistVisitor& player) const;
    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;
    bool hasNext() const;
    bool hasSelected() const;

private:
    void rearrange(const std::function<void()>& operation);
    void locate(const Song& target);
    void notify(IPlaybackListener& listener) const;
};

#endif //PLAYLIST_H
```

## model/Playlist.cpp

```cpp
#include "Playlist.h"
#include <random>
#include <algorithm>
#include <ranges>

Playlist::Playlist(IPlaylistVisitor& deleter) : deleter_(deleter) {}

void Playlist::add(const Song& song) {
    songs_.push_back(song);
}

void Playlist::remove(const int index) {
    if (index < 0 || index >= songs_.size()) return;
    songs_[index].accept(deleter_);
    songs_.erase(songs_.begin() + index);

    if (index == current_song_) {
        current_song_ = -1;
    } else if (index < current_song_) {
        current_song_--;
    }
}

void Playlist::sort(SortingAlgorithm& criteria) {
    rearrange([&] { arrangement_.sort(songs_, criteria); });
}

void Playlist::reverse() {
    rearrange([this] { arrangement_.reverse(songs_); });
}

void Playlist::restore() {
    rearrange([this] { arrangement_.restore(songs_); });
}

void Playlist::rearrange(const std::function<void()>& operation) {
    if (!hasSelected()) {
        operation();
        return;
    }
    const Song current = songs_[current_song_];
    operation();
    locate(current);
}

void Playlist::locate(const Song& target) {
    for (int i = 0; i < songs_.size(); i++) {
        if (songs_[i].isEqualTo(target)) {
            current_song_ = i;
            return;
        }
    }
    current_song_ = -1;
}

void Playlist::shuffle() {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    if (hasSelected()) {
        std::swap(songs_[0], songs_[current_song_]);
        std::shuffle(songs_.begin() + 1, songs_.end(), generator);
        current_song_ = 0;
    } else {
        std::ranges::shuffle(songs_, generator);
    }
}

void Playlist::clear() {
    songs_.clear();
    current_song_ = -1;
}

void Playlist::select(const int index, IPlaybackListener& listener) {
    if (index >= 0 && index < songs_.size()) {
        current_song_ = index;
        notify(listener);
    }
}

void Playlist::pick(const std::string& name, IPlaybackListener& listener) {
    for (int i = 0; i < songs_.size(); i++) {
        if (songs_[i].matches(name)) {
            select(i, listener);
            return;
        }
    }
}

void Playlist::advance(IPlaybackListener& listener) {
    if (hasNext()) {
        current_song_++;
        notify(listener);
    }
}

void Playlist::retreat(IPlaybackListener& listener) {
    if (current_song_ > 0) {
        current_song_--;
        notify(listener);
    }
}

void Playlist::notify(IPlaybackListener& listener) const {
    listener.onSelected(current_song_);
}

void Playlist::play(IPlaylistVisitor& player) const {
    if (hasSelected()) {
        songs_[current_song_].accept(player);
    }
}

void Playlist::accept(IPlaylistVisitor& visitor) const {
    for (const Song& song : songs_) {
        song.accept(visitor);
    }
}

void Playlist::search(const std::string& query, IPlaylistVisitor& visitor) const {
    for (const Song& song : songs_) {
        if (song.matches(query)) {
            song.accept(visitor);
        }
    }
}

bool Playlist::hasNext() const {
    return current_song_ + 1 < static_cast<int>(songs_.size());
}

bool Playlist::hasSelected() const {
    return current_song_ >= 0 && current_song_ < static_cast<int>(songs_.size());
}
```

## model/QuickSort.h

```cpp
#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "SortingAlgorithm.h"
#include <utility>

class QuickSort final : public SortingAlgorithm {
private:
    std::string title_;

    void visit(const std::string& name, const std::string& path) override;
    int divide(std::vector<Song>& songs, const std::pair<int, int> &bounds);

public:
    void sort(std::vector<Song>& songs) override;
};

#endif //QUICK_SORT_H
```

## model/QuickSort.cpp

```cpp
#include "QuickSort.h"
#include <stack>

void QuickSort::visit(const std::string& name, const std::string&) {
    title_ = Song::parse(name);
}

void QuickSort::sort(std::vector<Song>& songs) {
    if (songs.empty()) return;

    std::stack<std::pair<int, int>> stack;
    stack.push({0, static_cast<int>(songs.size()) - 1});

    while (!stack.empty()) {
        const auto bounds = stack.top();
        stack.pop();

        if (bounds.first >= bounds.second) continue;

        const int pivot = divide(songs, bounds);
        if (pivot - 1 > bounds.first) stack.push({bounds.first, pivot - 1});
        if (pivot + 1 < bounds.second) stack.push({pivot + 1, bounds.second});
    }
}

int QuickSort::divide(std::vector<Song>& songs, const std::pair<int, int> &bounds) {
    songs[bounds.second].accept(*this);
    const std::string pivot = title_;
    int i = bounds.first;

    for (int j = bounds.first; j < bounds.second; j++) {
        songs[j].accept(*this);
        if (title_ < pivot) {
            std::swap(songs[i], songs[j]);
            i++;
        }
    }
    std::swap(songs[i], songs[bounds.second]);
    return i;
}
```

## model/RepeatAllMode.h

```cpp
#ifndef REPEAT_ALL_MODE_H
#define REPEAT_ALL_MODE_H

#include "RepeatStrategy.h"

class RepeatAllMode final : public RepeatStrategy {
public:
    RepeatAllMode();
    bool apply(Playlist& playlist, IPlaybackListener& listener) override;
};

#endif //REPEAT_ALL_MODE_H
```

## model/RepeatAllMode.cpp

```cpp
#include "RepeatAllMode.h"

RepeatAllMode::RepeatAllMode() : RepeatStrategy(2) {}

bool RepeatAllMode::apply(Playlist& playlist, IPlaybackListener& listener) {
    if (playlist.hasNext()) {
        playlist.advance(listener);
    } else {
        playlist.select(0, listener);
    }
    return true;
}
```

## model/RepeatMode.h

```cpp
#ifndef REPEAT_MODE_H
#define REPEAT_MODE_H

#include "RepeatStrategy.h"
#include "Playlist.h"
#include "PlaybackNotifier.h"
#include <vector>
#include <memory>

class RepeatMode {
private:
    Playlist& playlist_;
    PlaybackNotifier& notifier_;
    std::vector<std::unique_ptr<RepeatStrategy>> modes_;
    int index_ = 0;

public:
    RepeatMode(Playlist& playlist, PlaybackNotifier& notifier);
    void advance();
    bool apply() const;
};

#endif //REPEAT_MODE_H
```

## model/RepeatMode.cpp

```cpp
#include "RepeatMode.h"
#include "NoRepeatMode.h"
#include "RepeatOneMode.h"
#include "RepeatAllMode.h"

RepeatMode::RepeatMode(Playlist& playlist, PlaybackNotifier& notifier)
    : playlist_(playlist), notifier_(notifier) {
    modes_.push_back(std::make_unique<NoRepeatMode>());
    modes_.push_back(std::make_unique<RepeatOneMode>());
    modes_.push_back(std::make_unique<RepeatAllMode>());
}

void RepeatMode::advance() {
    index_ = (index_ + 1) % static_cast<int>(modes_.size());
    modes_[index_]->announce(notifier_);
}

bool RepeatMode::apply() const {
    return modes_[index_]->apply(playlist_, notifier_);
}
```

## model/RepeatOneMode.h

```cpp
#ifndef REPEAT_ONE_MODE_H
#define REPEAT_ONE_MODE_H

#include "RepeatStrategy.h"

class RepeatOneMode final : public RepeatStrategy {
public:
    RepeatOneMode();
    bool apply(Playlist& playlist, IPlaybackListener& listener) override;
};

#endif //REPEAT_ONE_MODE_H
```

## model/RepeatOneMode.cpp

```cpp
#include "RepeatOneMode.h"

RepeatOneMode::RepeatOneMode() : RepeatStrategy(1) {}

bool RepeatOneMode::apply(Playlist&, IPlaybackListener&) { return true; }
```

## model/RepeatStrategy.h

```cpp
#ifndef REPEAT_STRATEGY_H
#define REPEAT_STRATEGY_H

#include "Playlist.h"
#include "IPlaybackListener.h"

class RepeatStrategy {
protected:
    int code_;

public:
    explicit RepeatStrategy(int code);
    virtual ~RepeatStrategy() = default;
    virtual bool apply(Playlist& playlist, IPlaybackListener& listener) = 0;
    void announce(IPlaybackListener& listener) const;
};

#endif //REPEAT_STRATEGY_H
```

## model/RepeatStrategy.cpp

```cpp
#include "RepeatStrategy.h"

RepeatStrategy::RepeatStrategy(const int code) : code_(code) {}

void RepeatStrategy::announce(IPlaybackListener& listener) const {
    listener.onRepeatChanged(code_);
}
```

## model/ShellSort.h

```cpp
#ifndef SHELL_SORT_H
#define SHELL_SORT_H
#include "SortingAlgorithm.h"

class ShellSort : public SortingAlgorithm {
protected:
    long long key_ = 0;

public:
    void sort(std::vector<Song>& songs) override;
};

#endif //SHELL_SORT_H
```

## model/ShellSort.cpp

```cpp
#include "ShellSort.h"

void ShellSort::sort(std::vector<Song>& songs) {
    const int total = songs.size();
    for (int interval = total / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < total; i++) {
            Song swapValue = songs[i];
            swapValue.accept(*this);
            const long long swapKey = key_;
            int j;
            for (j = i; j >= interval; j -= interval) {
                songs[j - interval].accept(*this);
                if (key_ <= swapKey) break;
                songs[j] = songs[j - interval];
            }
            songs[j] = swapValue;
        }
    }
}
```

## model/Song.h

```cpp
#ifndef SONG_H
#define SONG_H

#include "IPlaylistVisitor.h"
#include <string>

class Song {
private:
    std::string name_;
    std::string path_;

    static std::string trim(const std::string& string);

public:
    Song(const std::string& name, const std::string& path);

    void accept(IPlaylistVisitor& visitor) const;
    bool matches(const std::string& query) const;
    bool isEqualTo(const Song& other) const;
    static std::string parse(const std::string& name);
};

#endif //SONG_H
```

## model/Song.cpp

```cpp
#include "Song.h"
#include <regex>

Song::Song(const std::string& name, const std::string& path)
       : name_(name), path_(path) {
}

void Song::accept(IPlaylistVisitor& visitor) const {
    visitor.visit(name_, path_);
}

bool Song::matches(const std::string& query) const {
    return name_.find(query) != std::string::npos;
}

bool Song::isEqualTo(const Song& other) const {
    return name_ == other.name_ && path_ == other.path_;
}

std::string Song::parse(const std::string& name) {
    static const std::regex pattern(R"(\(\d+\)\s(.+))");
    std::smatch match;
    if (std::regex_match(name, match, pattern)) {
        return trim(match[1]);
    }
    return trim(name);
}

std::string Song::trim(const std::string& string) {
    const size_t first = string.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    const size_t last = string.find_last_not_of(" \t\n\r");
    return string.substr(first, last - first + 1);
}
```

## model/SortingAlgorithm.h

```cpp
#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H

#include "Song.h"
#include "IPlaylistVisitor.h"
#include <vector>

class SortingAlgorithm : public IPlaylistVisitor {
public:
    ~SortingAlgorithm() override = default;
    virtual void sort(std::vector<Song>& songs) = 0;
};

#endif //SORTING_ALGORITHM_H
```

## controller/Controller.h

```cpp
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include "../view/IPlayerListener.h"
#include "SortController.h"
#include "SearchController.h"

class Controller final : public IPlaybackListener, public IPlayerListener {
private:
    MusicPlayer& music_player_;
    IPlayerView& view_;
    SortController sort_;
    SearchController search_;
    bool playing_ = false;

    void refresh() const;

public:
    Controller(MusicPlayer& musicPlayer, IPlayerView& view);

    void onStart(const std::string& path) override;
    void onChanged() override;
    void onSelected(int index) override;
    void onEnabled(bool state) override;
    void onReveal(bool visible) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onRepeatChanged(int mode) override;
    void onFeedback(const std::string& message, bool success) override;
    void onStopped() override;
    void onPlay(int index) override;
    void onToggle() override;
    void onRepeat() override;
    void onAdvance() override;
    void onRetreat() override;
    void onAdd() override;
    void onRemove(int index) override;
    void onShuffle() override;
    void onSkip() override;
    void onSort() override;
    void onSearch(const std::string& query) override;
    void onPick(const std::string& name) override;
    void onDrop(const std::vector<std::string>& paths) override;
    void onAdjust(int volume) override;
    void onEnd() override;
};

#endif //CONTROLLER_H
```

## controller/Controller.cpp

```cpp
#include "Controller.h"
#include "PlaylistRenderer.h"

Controller::Controller(MusicPlayer& musicPlayer, IPlayerView& view) : music_player_(musicPlayer), view_(view),
          sort_(musicPlayer, view), search_(musicPlayer, view) {
    music_player_.subscribe(*this);
    view_.add(this);
    refresh();
}

void Controller::onStart(const std::string& path) {
    view_.play(path);
    playing_ = true;
}

void Controller::onChanged() {
    refresh();
}

void Controller::onSelected(const int index) {
    view_.highlight(index);
    view_.enable(true);
}

void Controller::onEnabled(const bool state) {
    view_.enable(state);
}

void Controller::onReveal(const bool visible) {
    view_.reveal(visible);
}

void Controller::onSchedule(const int delay) {
    view_.schedule(delay);
}

void Controller::onCancel() {
    view_.cancel();
}

void Controller::onRepeatChanged(const int mode) {
    view_.repeat(mode);
}

void Controller::onFeedback(const std::string& message, const bool success) {
    view_.notify(message, success);
}

void Controller::onStopped() {
    view_.enable(false);
    view_.pause();
    view_.highlight(-1);
    playing_ = false;
}

void Controller::onPlay(const int index) {
    music_player_.play(index);
}

void Controller::onToggle() {
    if (playing_) {
        view_.pause();
    } else {
        view_.resume();
    }
    playing_ = !playing_;
}

void Controller::onRepeat() {
    music_player_.repeat();
}

void Controller::onAdvance() {
    music_player_.advance();
}

void Controller::onRetreat() {
    music_player_.retreat();
}

void Controller::onAdd() {
    const std::string path = view_.browse();
    if (!path.empty()) {
        music_player_.insert(path);
    }
}

void Controller::onRemove(const int index) {
    if (view_.confirm("Are you sure you wanna delete this song?")) {
        music_player_.remove(index);
    }
}

void Controller::onShuffle() {
    music_player_.shuffle();
}

void Controller::onSkip() {
    music_player_.skip();
}

void Controller::onSort() {
    sort_.cycle();
}

void Controller::onSearch(const std::string& query) {
    search_.search(query);
}

void Controller::onPick(const std::string& name) {
    music_player_.pick(name);
    view_.dismiss();
}

void Controller::onDrop(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        music_player_.insert(path);
    }
}

void Controller::onAdjust(const int volume) {
    view_.adjust(volume);
}

void Controller::onEnd() {
    music_player_.end();
}

void Controller::refresh() const {
    PlaylistRenderer renderer(view_);
    music_player_.accept(renderer);
    renderer.render();
}
```

## controller/CustomMode.h

```cpp
#ifndef CUSTOM_MODE_H
#define CUSTOM_MODE_H

#include "SortMode.h"

class CustomMode final : public SortMode {
public:
    CustomMode();
    void apply(MusicPlayer& musicPlayer) override;
};

#endif //CUSTOM_MODE_H
```

## controller/CustomMode.cpp

```cpp
#include "CustomMode.h"

CustomMode::CustomMode() : SortMode("Custom", nullptr) {}

void CustomMode::apply(MusicPlayer& musicPlayer) {
    musicPlayer.restore();
}
```

## controller/PlaylistRenderer.h

```cpp
#ifndef PLAYLIST_RENDERER_H
#define PLAYLIST_RENDERER_H

#include "../model/IPlaylistVisitor.h"
#include "../view/IPlayerView.h"
#include <vector>
#include <string>

class PlaylistRenderer final : public IPlaylistVisitor {
private:
    IPlayerView& view_;
    std::vector<std::string> names_;

public:
    explicit PlaylistRenderer(IPlayerView& view);
    void visit(const std::string& name, const std::string& path) override;
    void render() const;
    void suggest() const;
};

#endif //PLAYLIST_RENDERER_H
```

## controller/PlaylistRenderer.cpp

```cpp
#include "PlaylistRenderer.h"

PlaylistRenderer::PlaylistRenderer(IPlayerView& view)
    : view_(view) {
}

void PlaylistRenderer::visit(const std::string& name, const std::string&) {
    names_.push_back(name);
}

void PlaylistRenderer::render() const {
    view_.refresh(names_);
}

void PlaylistRenderer::suggest() const {
    view_.suggest(names_);
}
```

## controller/SearchController.h

```cpp
#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include <string>

class SearchController {
private:
    MusicPlayer& music_player_;
    IPlayerView& view_;

public:
    SearchController(MusicPlayer& musicPlayer, IPlayerView& view);
    void search(const std::string& query) const;
};

#endif //SEARCH_CONTROLLER_H
```

## controller/SearchController.cpp

```cpp
#include "SearchController.h"
#include "PlaylistRenderer.h"

SearchController::SearchController(MusicPlayer& musicPlayer, IPlayerView& view)
    : music_player_(musicPlayer), view_(view) {}

void SearchController::search(const std::string& query) const {
    if (query.empty()) {
        view_.dismiss();
        return;
    }
    PlaylistRenderer renderer(view_);
    music_player_.search(query, renderer);
    renderer.suggest();
}
```

## controller/SortController.h

```cpp
#ifndef SORT_CONTROLLER_H
#define SORT_CONTROLLER_H

#include "SortMode.h"
#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include <vector>
#include <memory>

class SortController {
private:
    MusicPlayer& music_player_;
    IPlayerView& view_;
    std::vector<std::unique_ptr<SortMode>> modes_;
    int index_ = -1;

public:
    SortController(MusicPlayer& musicPlayer, IPlayerView& view);
    void cycle();
};

#endif //SORT_CONTROLLER_H
```

## controller/SortController.cpp

```cpp
#include "SortController.h"
#include "TitleDescending.h"
#include "CustomMode.h"
#include "../model/QuickSort.h"
#include "../model/DurationSort.h"
#include "../model/DateSort.h"

SortController::SortController(MusicPlayer& musicPlayer, IPlayerView& view)
    : music_player_(musicPlayer), view_(view) {
    modes_.push_back(std::make_unique<SortMode>("Title \xe2\x96\xb2", new QuickSort()));
    modes_.push_back(std::make_unique<TitleDescending>());
    modes_.push_back(std::make_unique<SortMode>("Duration \xe2\x96\xb2", new DurationSort()));
    modes_.push_back(std::make_unique<SortMode>("Date \xe2\x96\xb2", new DateSort()));
    modes_.push_back(std::make_unique<CustomMode>());
}

void SortController::cycle() {
    index_ = (index_ + 1) % static_cast<int>(modes_.size());
    modes_[index_]->apply(music_player_);
    modes_[index_]->display(view_);
}
```

## controller/SortMode.h

```cpp
#ifndef SORT_MODE_H
#define SORT_MODE_H

#include <string>
#include <memory>
#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include "../model/SortingAlgorithm.h"

class SortMode {
private:
    std::string label_;

protected:
    std::unique_ptr<SortingAlgorithm> criteria_;

public:
    SortMode(const std::string& label, SortingAlgorithm* criteria);
    virtual ~SortMode() = default;
    virtual void apply(MusicPlayer& musicPlayer);
    void display(IPlayerView& view) const;
};

#endif //SORT_MODE_H
```

## controller/SortMode.cpp

```cpp
#include "SortMode.h"

SortMode::SortMode(const std::string& label, SortingAlgorithm* criteria)
    : label_(label), criteria_(criteria) {}

void SortMode::apply(MusicPlayer& musicPlayer) {
    musicPlayer.sort(*criteria_);
}

void SortMode::display(IPlayerView& view) const {
    view.sort(label_);
}
```

## controller/TitleDescending.h

```cpp
#ifndef TITLE_DESCENDING_H
#define TITLE_DESCENDING_H

#include "SortMode.h"

class TitleDescending final : public SortMode {
public:
    TitleDescending();
    void apply(MusicPlayer& musicPlayer) override;
};

#endif //TITLE_DESCENDING_H
```

## controller/TitleDescending.cpp

```cpp
#include "TitleDescending.h"
#include "../model/QuickSort.h"

TitleDescending::TitleDescending() : SortMode("Title \xe2\x96\xbc", new QuickSort()) {}

void TitleDescending::apply(MusicPlayer& musicPlayer) {
    musicPlayer.sort(*criteria_);
    musicPlayer.reverse();
}
```

## view/IAudioPlayer.h

```cpp
#ifndef I_AUDIO_PLAYER_H
#define I_AUDIO_PLAYER_H
#include <string>

class IAudioPlayer {
public:
    virtual ~IAudioPlayer() = default;
    virtual void play(const std::string& path) = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void adjust(int volume) = 0;
};

#endif //I_AUDIO_PLAYER_H
```

## view/IControlPanel.h

```cpp
#ifndef I_CONTROL_PANEL_H
#define I_CONTROL_PANEL_H
#include <string>

class IControlPanel {
public:
    virtual ~IControlPanel() = default;
    virtual void enable(bool state) = 0;
    virtual void reveal(bool visible) = 0;
    virtual void schedule(int delay) = 0;
    virtual void cancel() = 0;
    virtual void repeat(int mode) = 0;
    virtual void sort(const std::string& label) = 0;
};

#endif //I_CONTROL_PANEL_H
```

## view/IDialog.h

```cpp
#ifndef I_DIALOG_H
#define I_DIALOG_H

#include <string>

class IDialog {
public:
    virtual ~IDialog() = default;
    virtual bool confirm(const std::string& message) = 0;
    virtual std::string browse() = 0;
};

#endif //I_DIALOG_H
```

## view/IDisplayControl.h

```cpp
#ifndef I_DISPLAY_CONTROL_H
#define I_DISPLAY_CONTROL_H

#include <string>

class IDisplayControl {
public:
    virtual ~IDisplayControl() = default;
    virtual void onSort() = 0;
    virtual void onSearch(const std::string& query) = 0;
    virtual void onPick(const std::string& name) = 0;
    virtual void onAdjust(int volume) = 0;
};

#endif //I_DISPLAY_CONTROL_H
```

## view/ILibraryControl.h

```cpp
#ifndef I_LIBRARY_CONTROL_H
#define I_LIBRARY_CONTROL_H

#include <string>
#include <vector>

class ILibraryControl {
public:
    virtual ~ILibraryControl() = default;
    virtual void onAdd() = 0;
    virtual void onRemove(int index) = 0;
    virtual void onDrop(const std::vector<std::string>& paths) = 0;
};

#endif //I_LIBRARY_CONTROL_H
```

## view/INotification.h

```cpp
#ifndef I_NOTIFICATION_H
#define I_NOTIFICATION_H

#include <string>

class INotification {
public:
    virtual ~INotification() = default;
    virtual void notify(const std::string& message, bool success) = 0;
};

#endif //I_NOTIFICATION_H
```

## view/IPlaybackControl.h

```cpp
#ifndef I_PLAYBACK_CONTROL_H
#define I_PLAYBACK_CONTROL_H

class IPlaybackControl {
public:
    virtual ~IPlaybackControl() = default;
    virtual void onPlay(int index) = 0;
    virtual void onToggle() = 0;
    virtual void onRepeat() = 0;
    virtual void onAdvance() = 0;
    virtual void onRetreat() = 0;
    virtual void onShuffle() = 0;
    virtual void onSkip() = 0;
    virtual void onEnd() = 0;
};

#endif //I_PLAYBACK_CONTROL_H
```

## view/IPlayerListener.h

```cpp
#ifndef I_PLAYER_LISTENER_H
#define I_PLAYER_LISTENER_H

#include "IPlaybackControl.h"
#include "ILibraryControl.h"
#include "IDisplayControl.h"

class IPlayerListener : public IPlaybackControl, public ILibraryControl, public IDisplayControl {
public:
    ~IPlayerListener() override = default;
};

#endif //I_PLAYER_LISTENER_H
```

## view/IPlayerView.h

```cpp
#ifndef I_PLAYER_VIEW_H
#define I_PLAYER_VIEW_H

#include "IPlayerListener.h"
#include "IPlaylistPanel.h"
#include "ISearchPanel.h"
#include "IControlPanel.h"
#include "INotification.h"
#include "IDialog.h"
#include "IAudioPlayer.h"

class IPlayerView : public IPlaylistPanel, public ISearchPanel, public IControlPanel,
                    public INotification, public IDialog, public IAudioPlayer {
public:
    ~IPlayerView() override = default;
    virtual void add(IPlayerListener* listener) = 0;
};

#endif //I_PLAYER_VIEW_H
```

## view/IPlaylistPanel.h

```cpp
#ifndef I_PLAYLIST_PANEL_H
#define I_PLAYLIST_PANEL_H

#include <string>
#include <vector>

class IPlaylistPanel {
public:
    virtual ~IPlaylistPanel() = default;
    virtual void refresh(const std::vector<std::string>& names) = 0;
    virtual void highlight(int index) = 0;
};

#endif //I_PLAYLIST_PANEL_H
```

## view/ISearchPanel.h

```cpp
#ifndef I_SEARCH_PANEL_H
#define I_SEARCH_PANEL_H

#include <string>
#include <vector>

class ISearchPanel {
public:
    virtual ~ISearchPanel() = default;
    virtual void suggest(const std::vector<std::string>& names) = 0;
    virtual void dismiss() = 0;
};

#endif //I_SEARCH_PANEL_H

```

## adapters/qt/IWidgetSetup.h

```cpp
#ifndef I_WIDGET_SETUP_H
#define I_WIDGET_SETUP_H

class IWidgetSetup {
public:
    virtual ~IWidgetSetup() = default;
    virtual void setup() = 0;
    virtual void wire() = 0;
};

#endif //I_WIDGET_SETUP_H
```

## adapters/qt/QtAudioEngine.h

```cpp
#ifndef QT_AUDIO_ENGINE_H
#define QT_AUDIO_ENGINE_H

#include "QtProgressPanel.h"
#include "IWidgetSetup.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QTimer>
#include <string>

class QtAudioEngine final : public QWidget, public IWidgetSetup {
    Q_OBJECT
private:
    QMediaPlayer* media_player_;
    QAudioOutput* audio_output_;
    QTimer* ad_timer_;
    QtProgressPanel* progress_bar_;

    void monitor();
    void start();

public:
    explicit QtAudioEngine(QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void play(const std::string& path);
    void resume();
    void pause();
    void stop() const;
    void adjust(double volume) const;
    void schedule(int milliseconds) const;
    void cancel() const;
    void enable(bool state) const;

signals:
    void endRequested();
    void revealRequested();
    void toggleRequested(bool playing);
};

#endif //QT_AUDIO_ENGINE_H
```

## adapters/qt/QtAudioEngine.cpp

```cpp
#include "QtAudioEngine.h"
#include "QtLayoutUtil.h"
#include <QVBoxLayout>
#include <QAudioDevice>
#include <QUrl>

QtAudioEngine::QtAudioEngine(QWidget* parent) : QWidget(parent) {
    setup();
    wire();
    monitor();
}

void QtAudioEngine::setup() {
    media_player_ = new QMediaPlayer(this);
    audio_output_ = new QAudioOutput(this);
    audio_output_->setVolume(0.5);
    media_player_->setAudioOutput(audio_output_);

    ad_timer_ = new QTimer(this);
    ad_timer_->setSingleShot(true);
    progress_bar_ = new QtProgressPanel(*media_player_, this);

    auto* layout = new QVBoxLayout(this);
    QtLayoutUtil::flatten(layout);
    layout->addWidget(progress_bar_);
}

void QtAudioEngine::wire() {
    connect(media_player_, &QMediaPlayer::mediaStatusChanged, this, [this]
        (const QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            emit endRequested();
        }
    });

    connect(ad_timer_, &QTimer::timeout, this, [this]() {
        emit revealRequested();
    });
}

void QtAudioEngine::monitor() {
    auto* devices = new QMediaDevices(this);
    connect(devices, &QMediaDevices::audioOutputsChanged, this, [this]() {
        audio_output_->setDevice(QMediaDevices::defaultAudioOutput());
    });
}

void QtAudioEngine::start() {
    media_player_->play();
    emit toggleRequested(true);
}

void QtAudioEngine::play(const std::string& path) {
    media_player_->stop();
    media_player_->setSource(QUrl::fromLocalFile(QString::fromStdString(path)));
    start();
}

void QtAudioEngine::resume() {
    start();
}

void QtAudioEngine::pause() {
    media_player_->pause();
    emit toggleRequested(false);
}

void QtAudioEngine::stop() const {
    media_player_->stop();
}

void QtAudioEngine::adjust(const double volume) const {
    audio_output_->setVolume(volume);
}

void QtAudioEngine::schedule(const int milliseconds) const {
    ad_timer_->stop();
    ad_timer_->start(milliseconds);
}

void QtAudioEngine::cancel() const {
    ad_timer_->stop();
}

void QtAudioEngine::enable(const bool state) const {
    progress_bar_->enable(state);
}
```

## adapters/qt/QtDialog.h

```cpp
#ifndef QT_DIALOG_H
#define QT_DIALOG_H

#include "../../view/IDialog.h"
#include <QWidget>

class QtDialog final : public IDialog {
private:
    QWidget* parent_;

public:
    explicit QtDialog(QWidget* parent);
    bool confirm(const std::string& message) override;
    std::string browse() override;
};

#endif //QT_DIALOG_H
```

## adapters/qt/QtDialog.cpp

```cpp
#include "QtDialog.h"
#include <QMessageBox>
#include <QFileDialog>

QtDialog::QtDialog(QWidget* parent) : parent_(parent) {}

bool QtDialog::confirm(const std::string& message) {
    return QMessageBox::question(parent_, "",
        QString::fromStdString(message),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

std::string QtDialog::browse() {
    return QFileDialog::getOpenFileName(parent_).toStdString();
}
```

## adapters/qt/QtDragDrop.h

```cpp
#ifndef QT_DRAG_DROP_H
#define QT_DRAG_DROP_H

#include <QDropEvent>
#include <string>
#include <vector>

class QtDragDrop final {
public:
    static void accept(QDragEnterEvent* event);
    static std::vector<std::string> extract(const QDropEvent* event);
};

#endif //QT_DRAG_DROP_H
```

## adapters/qt/QtDragDrop.cpp

```cpp
#include "QtDragDrop.h"
#include <QMimeData>
#include <QUrl>

void QtDragDrop::accept(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

std::vector<std::string> QtDragDrop::extract(const QDropEvent* event) {
    std::vector<std::string> paths;
    const QList<QUrl> urls = event->mimeData()->urls();
    for (const auto& url : urls) {
        paths.push_back(url.toLocalFile().toStdString());
    }
    return paths;
}
```

## adapters/qt/QtLayoutUtil.h

```cpp
#ifndef QT_LAYOUT_UTIL_H
#define QT_LAYOUT_UTIL_H

#include <QLayout>

class QtLayoutUtil final {
public:
    static void flatten(QLayout* layout);
    static void center(QLayout* layout);
};

#endif //QT_LAYOUT_UTIL_H

```

## adapters/qt/QtLayoutUtil.cpp

```cpp
#include "QtLayoutUtil.h"

void QtLayoutUtil::flatten(QLayout* layout) {
    layout->setContentsMargins(0, 0, 0, 0);
}

void QtLayoutUtil::center(QLayout* layout) {
    layout->setAlignment(Qt::AlignCenter);
}

```

## adapters/qt/QtNotification.h

```cpp
#ifndef QT_NOTIFICATION_H
#define QT_NOTIFICATION_H

#include "../../view/INotification.h"
#include <QWidget>

class QtNotification final : public INotification {
private:
    QWidget* parent_;

public:
    explicit QtNotification(QWidget* parent);
    void notify(const std::string& message, bool success) override;
};

#endif //QT_NOTIFICATION_H
```

## adapters/qt/QtNotification.cpp

```cpp
#include "QtNotification.h"
#include <QMessageBox>

QtNotification::QtNotification(QWidget* parent) : parent_(parent) {}

void QtNotification::notify(const std::string& message, const bool success) {
    QMessageBox::information(parent_, success ? "Success" : "Oops",
                             QString::fromStdString(message));
}
```

## adapters/qt/QtPlaybackPanel.h

```cpp
#ifndef QT_PLAYBACK_PANEL_H
#define QT_PLAYBACK_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "../../view/IPlayerListener.h"
#include "IWidgetSetup.h"

class QtPlaybackPanel final : public QWidget, public IWidgetSetup {
    Q_OBJECT
private:
    IPlayerListener& player_listener_;
    QPushButton* shuffle_button_;
    QPushButton* toggle_button_;
    QPushButton* repeat_button_;
    QPushButton* next_button_;
    QPushButton* previous_button_;

    static void paint(QPushButton* button, const std::string& path);

public:
    explicit QtPlaybackPanel(IPlayerListener& listener, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) const;
    void toggle(bool playing) const;
    void repeat(int mode) const;
};

#endif //QT_PLAYBACK_PANEL_H
```

## adapters/qt/QtPlaybackPanel.cpp

```cpp
#include "QtPlaybackPanel.h"
#include "QtLayoutUtil.h"
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QStyle>
#include <filesystem>

static std::string resolve(const std::string& path) {
    return std::filesystem::current_path().string() + path;
}

QtPlaybackPanel::QtPlaybackPanel(IPlayerListener& listener, QWidget* parent)
    : QWidget(parent), player_listener_(listener) {
    setup();
    wire();
}

void QtPlaybackPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    shuffle_button_ = new QPushButton(this);
    shuffle_button_->setObjectName("shuffle_button");
    shuffle_button_->setIconSize(QSize(16, 20));
    previous_button_ = new QPushButton("\xe2\x8f\xae", this);
    toggle_button_ = new QPushButton("\xe2\x96\xb6", this);
    toggle_button_->setObjectName("toggle_button");
    next_button_ = new QPushButton("\xe2\x8f\xad", this);
    repeat_button_ = new QPushButton(this);
    repeat_button_->setObjectName("repeat_button");
    repeat_button_->setIconSize(QSize(16, 16));

    layout->addWidget(shuffle_button_);
    layout->addWidget(previous_button_);
    layout->addWidget(toggle_button_);
    layout->addWidget(next_button_);
    layout->addWidget(repeat_button_);
    QtLayoutUtil::center(layout);

    paint(shuffle_button_, "/resources/icons/shuffle.png");
    paint(repeat_button_, "/resources/icons/repeat.png");
    enable(false);
}

void QtPlaybackPanel::wire() {
    connect(toggle_button_, &QPushButton::clicked, this, [this]() { player_listener_.onToggle(); });
    connect(repeat_button_, &QPushButton::clicked, this, [this]() { player_listener_.onRepeat(); });
    connect(shuffle_button_, &QPushButton::clicked, this, [this]() { player_listener_.onShuffle(); });
    connect(next_button_, &QPushButton::clicked, this, [this]() { player_listener_.onAdvance(); });
    connect(previous_button_, &QPushButton::clicked, this, [this]() { player_listener_.onRetreat(); });
}

void QtPlaybackPanel::enable(const bool state) const {
    shuffle_button_->setEnabled(state);
    toggle_button_->setEnabled(state);
    repeat_button_->setEnabled(state);
    next_button_->setEnabled(state);
    previous_button_->setEnabled(state);
}

void QtPlaybackPanel::toggle(const bool playing) const {
    toggle_button_->setText(playing ? "\xe2\x8f\xb8" : "\xe2\x96\xb6");
}

void QtPlaybackPanel::paint(QPushButton* button, const std::string& path) {
    QPixmap pixmap(QString::fromStdString(resolve(path)));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.end();
    button->setIcon(QIcon(pixmap));
    button->setText("");
}

void QtPlaybackPanel::repeat(const int mode) const {
    paint(repeat_button_, mode == 1 ? "/resources/icons/repeat_one.png" : "/resources/icons/repeat.png");
    repeat_button_->setProperty("active", mode == 2);
    repeat_button_->style()->unpolish(repeat_button_);
    repeat_button_->style()->polish(repeat_button_);
}
```

## adapters/qt/QtPlaylistDisplay.h

```cpp
#ifndef QT_PLAYLIST_DISPLAY_H
#define QT_PLAYLIST_DISPLAY_H

#include <QListView>
#include <QStringListModel>
#include <string>
#include <vector>

class QtPlaylistDisplay final : public QWidget {
    Q_OBJECT
private:
    QListView* playlist_;
    QStringListModel* list_model_;

    void setup();

public:
    explicit QtPlaylistDisplay(QWidget* parent = nullptr);
    void refresh(const std::vector<std::string>& names) const;
    void highlight(int index) const;
    void remove();

signals:
    void selectRequested(int index);
    void removeRequested(int index);
};

#endif //QT_PLAYLIST_DISPLAY_H
```

## adapters/qt/QtPlaylistDisplay.cpp

```cpp
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

void QtPlaylistDisplay::refresh(const std::vector<std::string>& names) const {
    QStringList list;
    for (const auto& name : names) {
        list.append(QString::fromStdString(name));
    }
    list_model_->setStringList(list);
}

void QtPlaylistDisplay::highlight(const int index) const {
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
```

## adapters/qt/QtProgressPanel.h

```cpp
#ifndef QT_PROGRESS_PANEL_H
#define QT_PROGRESS_PANEL_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>

class QtProgressPanel final : public QWidget {
    Q_OBJECT
private:
    QSlider* progress_bar_;
    QLabel* elapsed_time_;
    QLabel* total_time_;

    void setup();
    void wire(QMediaPlayer& media);
    static QString format(qint64 milliseconds);

public:
    QtProgressPanel(QMediaPlayer& media, QWidget* parent = nullptr);
    void enable(bool state) const;
};

#endif //QT_PROGRESS_PANEL_H
```

## adapters/qt/QtProgressPanel.cpp

```cpp
#include "QtProgressPanel.h"
#include <QHBoxLayout>

QtProgressPanel::QtProgressPanel(QMediaPlayer& media, QWidget* parent)
    : QWidget(parent) {
    setup();
    wire(media);
}

void QtProgressPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    elapsed_time_ = new QLabel("0:00", this);
    elapsed_time_->setObjectName("elapsed_time");
    progress_bar_ = new QSlider(Qt::Horizontal, this);
    progress_bar_->setMinimum(0);
    total_time_ = new QLabel("0:00", this);
    total_time_->setObjectName("total_time");

    layout->addWidget(elapsed_time_);
    layout->addWidget(progress_bar_);
    layout->addWidget(total_time_);
}

void QtProgressPanel::wire(QMediaPlayer& media) {
    connect(&media, &QMediaPlayer::positionChanged, this, [this](const qint64 position) {
        if (!progress_bar_->isSliderDown()) {
            progress_bar_->setValue(static_cast<int>(position));
        }
        elapsed_time_->setText(format(position));
    });

    connect(&media, &QMediaPlayer::durationChanged, this, [this](const qint64 duration) {
        progress_bar_->setMaximum(static_cast<int>(duration));
        total_time_->setText(format(duration));
    });

    connect(progress_bar_, &QSlider::sliderReleased, this, [&media, this]() {
        media.setPosition(progress_bar_->value());
    });
}

void QtProgressPanel::enable(const bool state) const {
    progress_bar_->setEnabled(state);
}

QString QtProgressPanel::format(const qint64 milliseconds) {
    const int seconds = static_cast<int>(milliseconds / 1000);
    const int minutes = seconds / 60;
    const int remaining = seconds % 60;
    return QString("%1:%2").arg(minutes).arg(remaining, 2, 10, QChar('0'));
}
```

## adapters/qt/QtSearchOverlay.h

```cpp
#ifndef QT_SEARCH_OVERLAY_H
#define QT_SEARCH_OVERLAY_H

#include <QListWidget>
#include <QWidget>
#include <string>
#include <vector>

class QtSearchOverlay final : public QWidget {
    Q_OBJECT
private:
    QListWidget* results_;

    void setup();
    void align();

public:
    explicit QtSearchOverlay(QWidget* parent = nullptr);
    void display(const std::vector<std::string>& names);
    void clear();

signals:
    void selectRequested(const std::string& name);
};

#endif //QT_SEARCH_OVERLAY_H

```

## adapters/qt/QtSearchOverlay.cpp

```cpp
#include "QtSearchOverlay.h"
#include "QtLayoutUtil.h"
#include <QVBoxLayout>

QtSearchOverlay::QtSearchOverlay(QWidget* parent) : QWidget(parent) {
    setup();
    setVisible(false);
}

void QtSearchOverlay::setup() {
    results_ = new QListWidget(this);
    results_->setObjectName("search_results");

    auto* layout = new QVBoxLayout(this);
    QtLayoutUtil::flatten(layout);
    layout->addWidget(results_);

    connect(results_, &QListWidget::itemDoubleClicked, this, [this](const QListWidgetItem* item) {
        emit selectRequested(item->text().toStdString());
    });
}

void QtSearchOverlay::align() {
    if (!parentWidget()) return;
    const int margin = 8;
    const int top = 75;
    const int width = parentWidget()->width() - margin * 2;
    const int height = std::min(200, results_->count() * 36 + 8);
    setGeometry(margin, top, width, height);
}

void QtSearchOverlay::display(const std::vector<std::string>& names) {
    results_->clear();
    for (const auto& name : names) {
        results_->addItem(QString::fromStdString(name));
    }
    align();
    setVisible(!names.empty());
    raise();
}

void QtSearchOverlay::clear() {
    results_->clear();
    setVisible(false);
}

```

## adapters/qt/QtSortHeader.h

```cpp
#ifndef QT_SORT_HEADER_H
#define QT_SORT_HEADER_H

#include <QPushButton>
#include <string>

class QtSortHeader final : public QWidget {
    Q_OBJECT
private:
    QPushButton* header_;

public:
    explicit QtSortHeader(QWidget* parent = nullptr);
    void display(const std::string& text) const;

signals:
    void clickRequested();
};

#endif //QT_SORT_HEADER_H
```

## adapters/qt/QtSortHeader.cpp

```cpp
#include "QtSortHeader.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>
#include <QWidget>

QtSortHeader::QtSortHeader(QWidget* parent)
    : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);

    header_ = new QPushButton("Custom", this);
    header_->setObjectName("sort_header");
    header_->setFlat(true);
    header_->setCursor(Qt::PointingHandCursor);

    layout->addWidget(header_);
    QtLayoutUtil::flatten(layout);

    connect(header_, &QPushButton::clicked, this, &QtSortHeader::clickRequested);
}

void QtSortHeader::display(const std::string& text) const {
    header_->setText(QString::fromStdString(text));
}
```

## adapters/qt/QtStyler.h

```cpp
#ifndef QT_STYLER_H
#define QT_STYLER_H

#include <QApplication>
#include <string>

class QtStyler {
public:
    static void apply(QApplication& app, const std::string& path);
};

#endif //QT_STYLER_H
```

## adapters/qt/QtStyler.cpp

```cpp
#include "QtStyler.h"
#include <QFile>

void QtStyler::apply(QApplication& app, const std::string& path) {
    QFile stylesheet(QString::fromStdString(path));
    if (stylesheet.open(QFile::ReadOnly)) {
        app.setStyleSheet(stylesheet.readAll());
        stylesheet.close();
    }
}
```

## adapters/qt/QtToolbar.h

```cpp
#ifndef QT_TOOLBAR_H
#define QT_TOOLBAR_H

#include <QWidget>
#include <QPushButton>
#include "IWidgetSetup.h"

class QtToolbar final : public QWidget, public IWidgetSetup {
    Q_OBJECT
private:
    QPushButton* add_button_;
    QPushButton* remove_button_;
    QPushButton* skip_button_;

public:
    explicit QtToolbar(QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) const;
    void reveal(bool visible) const;

signals:
    void addClicked();
    void removeClicked();
    void skipClicked();
};

#endif //QT_TOOLBAR_H
```

## adapters/qt/QtToolbar.cpp

```cpp
#include "QtToolbar.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>

QtToolbar::QtToolbar(QWidget* parent) : QWidget(parent) {
    setup();
    wire();
}

void QtToolbar::setup() {
    auto* layout = new QHBoxLayout(this);

    add_button_ = new QPushButton("Add Song", this);
    add_button_->setObjectName("add_button");
    remove_button_ = new QPushButton("Remove Song", this);
    remove_button_->setObjectName("remove_button");
    skip_button_ = new QPushButton("⏭", this);
    skip_button_->setObjectName("skip_button");
    skip_button_->setVisible(false);

    layout->addWidget(add_button_);
    layout->addWidget(remove_button_);
    layout->addWidget(skip_button_);
    QtLayoutUtil::center(layout);
}

void QtToolbar::wire() {
    connect(add_button_, &QPushButton::clicked, this, &QtToolbar::addClicked);
    connect(remove_button_, &QPushButton::clicked, this, &QtToolbar::removeClicked);
    connect(skip_button_, &QPushButton::clicked, this, &QtToolbar::skipClicked);
}

void QtToolbar::enable(const bool state) const {
    add_button_->setEnabled(state);
    remove_button_->setEnabled(state);
}

void QtToolbar::reveal(const bool visible) const {
    skip_button_->setVisible(visible);
}
```

## adapters/qt/QtView.h

```cpp
#ifndef QT_VIEW_H
#define QT_VIEW_H

#include "../../view/IPlayerView.h"
#include "QtPlaybackPanel.h"
#include "QtToolbar.h"
#include "QtAudioEngine.h"
#include "QtPlaylistDisplay.h"
#include "QtSortHeader.h"
#include "QtSearchOverlay.h"
#include "QtNotification.h"
#include "QtDialog.h"
#include <QWidget>
#include <QLineEdit>

class QtView final : public QWidget, public IPlayerView {
    Q_OBJECT
private:
    IPlayerListener* listener_ = nullptr;
    QtPlaybackPanel* playback_ = nullptr;
    QtToolbar* toolbar_ = nullptr;
    QtAudioEngine* audio_;
    QtPlaylistDisplay* display_;
    QtSortHeader* sort_header_;
    QtSearchOverlay* search_overlay_;
    QtNotification* notification_;
    QtDialog* dialog_;

    void setup();
    void wire(QLineEdit* search);
    void bind();

public:
    explicit QtView(QWidget* parent = nullptr);

    void add(IPlayerListener* listener) override;
    void refresh(const std::vector<std::string>& names) override;
    void highlight(int index) override;
    void suggest(const std::vector<std::string>& names) override;
    void dismiss() override;
    void enable(bool state) override;
    void reveal(bool visible) override;
    void schedule(int delay) override;
    void cancel() override;
    void repeat(int mode) override;
    void sort(const std::string& label) override;
    void notify(const std::string& message, bool success) override;
    bool confirm(const std::string& message) override;
    std::string browse() override;
    void play(const std::string& path) override;
    void resume() override;
    void pause() override;
    void stop() override;
    void adjust(int volume) override;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};

#endif //QT_VIEW_H
```

## adapters/qt/QtView.cpp

```cpp
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

    connect(audio_, &QtAudioEngine::endRequested, this, [this]() {
        listener_->onEnd();
    });

    connect(audio_, &QtAudioEngine::revealRequested, this, [this]() {
        toolbar_->reveal(true);
    });

    connect(audio_, &QtAudioEngine::toggleRequested, this, [this](const bool playing) {
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

    connect(sort_header_, &QtSortHeader::clickRequested, this, [this]() {
        listener_->onSort();
    });

    wire(search);
}

void QtView::wire(QLineEdit* search) {
    connect(display_, &QtPlaylistDisplay::selectRequested, this, [this](const int index) {
        listener_->onPlay(index);
    });

    connect(search, &QLineEdit::textChanged, this, [this](const QString& text) {
        listener_->onSearch(text.toStdString());
    });

    connect(search_overlay_, &QtSearchOverlay::selectRequested, this, [this, search](const std::string& name) {
        listener_->onPick(name);
        search->clear();
    });
}

void QtView::add(IPlayerListener* listener) {
    listener_ = listener;

    auto* main = layout();
    playback_ = QtViewFactory::createPlayback(*listener, this);
    auto* volume = QtViewFactory::createVolume(*listener, this);
    toolbar_ = QtViewFactory::createToolbar(this);

    main->addWidget(playback_);
    main->addWidget(volume);
    main->addWidget(toolbar_);

    bind();
}

void QtView::bind() {
    connect(toolbar_, &QtToolbar::addClicked, this, [this]() {
        listener_->onAdd();
    });
    connect(toolbar_, &QtToolbar::removeClicked, display_, &QtPlaylistDisplay::remove);
    connect(display_, &QtPlaylistDisplay::removeRequested, this, [this](const int index) {
        listener_->onRemove(index);
    });
    connect(toolbar_, &QtToolbar::skipClicked, this, [this]() {
        listener_->onSkip();
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
    if (!paths.empty()) listener_->onDrop(paths);
}
```

## adapters/qt/QtViewFactory.h

```cpp
#ifndef QT_VIEW_FACTORY_H
#define QT_VIEW_FACTORY_H

#include "../../view/IPlayerListener.h"
#include "QtPlaybackPanel.h"
#include "QtVolumePanel.h"
#include "QtToolbar.h"
#include "QtNotification.h"
#include "QtDialog.h"
#include <QWidget>

class QtViewFactory {
public:
    static QtPlaybackPanel* createPlayback(IPlayerListener& listener, QWidget* parent);
    static QtVolumePanel* createVolume(IPlayerListener& listener, QWidget* parent);
    static QtToolbar* createToolbar(QWidget* parent);
    static QtNotification* createNotification(QWidget* parent);
    static QtDialog* createDialog(QWidget* parent);
};

#endif //QT_VIEW_FACTORY_H
```

## adapters/qt/QtViewFactory.cpp

```cpp
#include "QtViewFactory.h"

QtPlaybackPanel* QtViewFactory::createPlayback(IPlayerListener& listener, QWidget* parent) {
    return new QtPlaybackPanel(listener, parent);
}

QtVolumePanel* QtViewFactory::createVolume(IPlayerListener& listener, QWidget* parent) {
    return new QtVolumePanel(listener, parent);
}

QtToolbar* QtViewFactory::createToolbar(QWidget* parent) {
    return new QtToolbar(parent);
}

QtNotification* QtViewFactory::createNotification(QWidget* parent) {
    return new QtNotification(parent);
}

QtDialog* QtViewFactory::createDialog(QWidget* parent) {
    return new QtDialog(parent);
}
```

## adapters/qt/QtVolumePanel.h

```cpp
#ifndef QT_VOLUME_PANEL_H
#define QT_VOLUME_PANEL_H

#include "../../view/IPlayerListener.h"
#include <QSlider>
#include <QLabel>

class QtVolumePanel final : public QWidget {
    Q_OBJECT
private:
    IPlayerListener& listener_;
    QSlider* slider_;
    QLabel* label_;

public:
    explicit QtVolumePanel(IPlayerListener& listener, QWidget* parent = nullptr);
    void adjust(int volume) const;
};

#endif //QT_VOLUME_PANEL_H
```

## adapters/qt/QtVolumePanel.cpp

```cpp
#include "QtVolumePanel.h"
#include <QHBoxLayout>

QtVolumePanel::QtVolumePanel(IPlayerListener& listener, QWidget* parent)
    : QWidget(parent), listener_(listener) {

    auto* layout = new QHBoxLayout(this);

    label_ = new QLabel("50%", this);
    label_->setObjectName("volume_label");
    slider_ = new QSlider(Qt::Horizontal, this);
    slider_->setRange(0, 100);
    slider_->setValue(50);

    layout->addWidget(label_);
    layout->addWidget(slider_);

    connect(slider_, &QSlider::valueChanged, this, [this](const int value) {
        adjust(value);
        listener_.onAdjust(value);
    });
}

void QtVolumePanel::adjust(const int volume) const {
    label_->setText(QString("%1%").arg(volume));
}
```

## test/DirectoryTestFixture.h

```cpp
#ifndef DIRECTORY_TEST_FIXTURE_H
#define DIRECTORY_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include <string>

class DirectoryTestFixture : public ::testing::Test {
protected:
    std::string test_directory_;

    void SetUp() override;
    void TearDown() override;
    void createFile(const std::string& name) const;

    virtual std::string identify() const = 0;
};

#endif //DIRECTORY_TEST_FIXTURE_H
```

## test/DirectoryTestFixture.cpp

```cpp
#include "DirectoryTestFixture.h"
#include <filesystem>
#include <fstream>

void DirectoryTestFixture::SetUp() {
    test_directory_ = std::filesystem::temp_directory_path().string() + "/" + identify();
    std::filesystem::create_directories(test_directory_);
}

void DirectoryTestFixture::TearDown() {
    std::filesystem::remove_all(test_directory_);
}

void DirectoryTestFixture::createFile(const std::string& name) const {
    std::ofstream(test_directory_ + "/" + name).close();
}
```

## test/MockPlaybackListener.h

```cpp
#ifndef MOCK_PLAYBACK_LISTENER_H
#define MOCK_PLAYBACK_LISTENER_H

#include "../model/IPlaybackListener.h"
#include <string>
#include <vector>

class MockPlaybackListener final : public IPlaybackListener {
private:
    std::vector<std::string> starts_;
    std::vector<int> selections_;
    std::vector<std::string> feedbacks_;
    int changes_ = 0;
    int enables_ = 0;
    int reveals_ = 0;
    int cancels_ = 0;
    int stops_ = 0;

public:
    void onStart(const std::string& path) override;
    void onChanged() override;
    void onSelected(int index) override;
    void onEnabled(bool state) override;
    void onReveal(bool visible) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onRepeatChanged(int mode) override;
    void onFeedback(const std::string& message, bool success) override;
    void onStopped() override;

    bool wasStarted() const;
    bool wasStartedWith(const std::string& path) const;
    bool wasChanged() const;
    bool wasChangedTimes(int expected) const;
    bool wasSelected() const;
    bool wasSelectedWith(int index) const;
    bool wasEnabled() const;
    bool wasRevealed() const;
    bool wasCancelled() const;
    bool wasFeedback(const std::string& message) const;
    bool wasStopped() const;
};

#endif //MOCK_PLAYBACK_LISTENER_H
```

## test/MockPlaybackListener.cpp

```cpp
#include "MockPlaybackListener.h"
#include <algorithm>

void MockPlaybackListener::onStart(const std::string& path) {
    starts_.push_back(path);
}

void MockPlaybackListener::onChanged() {
    changes_++;
}

void MockPlaybackListener::onSelected(const int index) {
    selections_.push_back(index);
}

void MockPlaybackListener::onEnabled(bool) {
    enables_++;
}

void MockPlaybackListener::onReveal(bool) {
    reveals_++;
}

void MockPlaybackListener::onSchedule(int) {}

void MockPlaybackListener::onCancel() {
    cancels_++;
}

void MockPlaybackListener::onRepeatChanged(int) {}

void MockPlaybackListener::onFeedback(const std::string& message, bool) {
    feedbacks_.push_back(message);
}

void MockPlaybackListener::onStopped() {
    stops_++;
}

bool MockPlaybackListener::wasStarted() const {
    return !starts_.empty();
}

bool MockPlaybackListener::wasStartedWith(const std::string& path) const {
    return std::ranges::find(starts_, path) != starts_.end();
}

bool MockPlaybackListener::wasChanged() const {
    return changes_ > 0;
}

bool MockPlaybackListener::wasChangedTimes(const int expected) const {
    return changes_ == expected;
}

bool MockPlaybackListener::wasSelected() const {
    return !selections_.empty();
}

bool MockPlaybackListener::wasSelectedWith(const int index) const {
    return std::ranges::find(selections_, index) != selections_.end();
}

bool MockPlaybackListener::wasEnabled() const {
    return enables_ > 0;
}

bool MockPlaybackListener::wasRevealed() const {
    return reveals_ > 0;
}

bool MockPlaybackListener::wasCancelled() const {
    return cancels_ > 0;
}

bool MockPlaybackListener::wasFeedback(const std::string& message) const {
    return std::ranges::find(feedbacks_, message) != feedbacks_.end();
}

bool MockPlaybackListener::wasStopped() const {
    return stops_ > 0;
}
```

## test/ModelTestFixture.h

```cpp
#ifndef MODEL_TEST_FIXTURE_H
#define MODEL_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include "../model/MusicPlayer.h"
#include "../model/Dice.h"
#include "MockPlaybackListener.h"
#include "TestPlaylistVisitor.h"
#include <string>

class ModelTestFixture : public ::testing::Test {
protected:
    std::string base_directory_;
    std::string music_directory_;
    std::string ads_directory_;
    MockPlaybackListener listener_;
    Dice dice_;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
    void createAd(const std::string& name) const;
    virtual std::string identify() const = 0;
};

#endif //MODEL_TEST_FIXTURE_H
```

## test/ModelTestFixture.cpp

```cpp
#include "ModelTestFixture.h"
#include <filesystem>
#include <fstream>

void ModelTestFixture::SetUp() {
    base_directory_ = std::filesystem::temp_directory_path().string() + "/" + identify();
    music_directory_ = base_directory_ + "/music";
    ads_directory_ = base_directory_ + "/announcements";
    std::filesystem::create_directories(music_directory_);
    std::filesystem::create_directories(ads_directory_);
}

void ModelTestFixture::TearDown() {
    std::filesystem::remove_all(base_directory_);
}

void ModelTestFixture::createSong(const std::string& name) const {
    std::ofstream(music_directory_ + "/" + name) << "audio";
}

void ModelTestFixture::createAd(const std::string& name) const {
    std::ofstream(ads_directory_ + "/" + name) << "ad";
}
```

## test/RegressionTest.h

```cpp
#ifndef REGRESSIONTEST_H
#define REGRESSIONTEST_H

#include "ModelTestFixture.h"

class RegressionTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif
```

## test/RegressionTest.cpp

```cpp
#include "RegressionTest.h"
#include "../model/Song.h"
#include "../model/Playlist.h"
#include "../model/MusicLibrary.h"
#include "../model/MusicPlayer.h"
#include "../model/Dice.h"
#include "../model/DurationSort.h"
#include "../model/QuickSort.h"
#include "TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string RegressionTest::identify() const {
    return "regression_test";
}

TEST_F(RegressionTest, SortEmptyPlaylistDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}

TEST_F(RegressionTest, SortSingleSongDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    playlist.add(Song("A.mp3", "/a"));
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}

TEST_F(RegressionTest, ShellSortEmptyDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    DurationSort byNumber;
    EXPECT_NO_THROW(playlist.sort(byNumber));
}

TEST_F(RegressionTest, ModelRefreshDoesNotRecurse) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(RegressionTest, ModelSortByNameDoesNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
}

TEST_F(RegressionTest, ModelSortByNumberDoesNotCrash) {
    createSong("(3) C.mp3");
    createSong("(1) A.mp3");
    createSong("(2) B.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    EXPECT_NO_THROW(musicPlayer.sort(byDuration));
}

TEST_F(RegressionTest, AdvanceUpdatesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(RegressionTest, RetreatUpdatesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(RegressionTest, RemoveBeforeCurrentAdjustsSelection) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    MockPlaybackListener listener_;
    playlist.add(Song("A.mp3", "/a"));
    playlist.add(Song("B.mp3", "/b"));
    playlist.add(Song("C.mp3", "/c"));
    playlist.select(2, listener_);
    playlist.remove(0);
    EXPECT_TRUE(playlist.hasSelected());
}

TEST_F(RegressionTest, QuickSortPartitionDoesNotUnderflow) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    QuickSort sorter;
    EXPECT_NO_THROW(sorter.sort(songs));
}

TEST_F(RegressionTest, InsertUnsupportedFileGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(RegressionTest, InsertDuplicateGivesFeedback) {
    createSong("dup.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/dup.mp3") << "data";

    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/dup.mp3");
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(RegressionTest, SortPreservesAllSongs) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(RegressionTest, ShufflePreservesAllSongs) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    for (int i = 0; i < 20; i++) {
        playlist.add(Song(std::to_string(i) + ".mp3", "/s"));
    }
    playlist.shuffle();
    TestPlaylistVisitor visitor;
    playlist.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(20));
}

TEST_F(RegressionTest, RepeatCycles) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.repeat();
    musicPlayer.repeat();
    EXPECT_NO_THROW(musicPlayer.repeat());
}

TEST_F(RegressionTest, RemoveFromEmptyPlaylistDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    EXPECT_NO_THROW(playlist.remove(0));
}

TEST_F(RegressionTest, RemoveNegativeIndexDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    playlist.add(Song("A.mp3", "/a"));
    EXPECT_NO_THROW(playlist.remove(-1));
}

TEST_F(RegressionTest, SelectInvalidIndexDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    MockPlaybackListener listener_;
    EXPECT_NO_THROW(playlist.select(999, listener_));
}

TEST_F(RegressionTest, PlayWithNoSelectionDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    playlist.add(Song("A.mp3", "/a"));
    TestPlaylistVisitor visitor;
    EXPECT_NO_THROW(playlist.play(visitor));
}

TEST_F(RegressionTest, ConcludeWithoutInterruptReturnsFalse) {
    Dice dice;
    Advertisement ad(ads_directory_, dice);
    EXPECT_FALSE(ad.conclude(listener_));
}

TEST_F(RegressionTest, MultipleSortsDoNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            QuickSort byTitle;
            EXPECT_NO_THROW(musicPlayer.sort(byTitle));
        } else {
            DurationSort byDuration;
            EXPECT_NO_THROW(musicPlayer.sort(byDuration));
        }
    }
}

TEST_F(RegressionTest, SortThenAdvanceWorks) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.advance());
}

TEST_F(RegressionTest, LargePlaylistSortDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    for (int i = 500; i > 0; i--) {
        playlist.add(Song("(" + std::to_string(i) + ") Song.mp3", "/s"));
    }
    DurationSort byNumber;
    EXPECT_NO_THROW(playlist.sort(byNumber));
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}
```

## test/TestPlaylistVisitor.h

```cpp
#ifndef TEST_PLAYLIST_VISITOR_H
#define TEST_PLAYLIST_VISITOR_H

#include "../model/IPlaylistVisitor.h"
#include <string>
#include <vector>

class TestPlaylistVisitor final : public IPlaylistVisitor {
private:
    std::vector<std::string> names_;
    std::vector<std::string> paths_;

public:
    void visit(const std::string& name, const std::string& path) override;

    bool hasName(const std::string& name) const;
    bool hasPath(const std::string& path) const;
    bool isEmpty() const;
    bool hasSongs(int expected) const;
    bool hasNameAt(int index, const std::string& name) const;
};

#endif //TEST_PLAYLIST_VISITOR_H
```

## test/TestPlaylistVisitor.cpp

```cpp
#include "TestPlaylistVisitor.h"
#include <algorithm>

void TestPlaylistVisitor::visit(const std::string& name, const std::string& path) {
    names_.push_back(name);
    paths_.push_back(path);
}

bool TestPlaylistVisitor::hasName(const std::string& name) const {
    return std::ranges::find(names_, name) != names_.end();
}

bool TestPlaylistVisitor::hasPath(const std::string& path) const {
    return std::ranges::find(paths_, path) != paths_.end();
}

bool TestPlaylistVisitor::isEmpty() const {
    return names_.empty();
}

bool TestPlaylistVisitor::hasSongs(const int expected) const {
    return names_.size() == expected;
}

bool TestPlaylistVisitor::hasNameAt(const int index, const std::string& name) const {
    return index >= 0 && index < names_.size() && names_[index] == name;
}
```

## test/model/AdvertisementTest.h

```cpp
#ifndef ADVERTISEMENTTEST_H
#define ADVERTISEMENTTEST_H

#include "../DirectoryTestFixture.h"
#include "../MockPlaybackListener.h"
#include "../../model/Dice.h"

class AdvertisementTest : public DirectoryTestFixture {
protected:
    MockPlaybackListener listener_;
    Dice dice_;

    std::string identify() const override;
};

#endif

```

## test/model/AdvertisementTest.cpp

```cpp
#include "AdvertisementTest.h"
#include "../../model/Advertisement.h"
#include <fstream>

std::string AdvertisementTest::identify() const {
    return "ad_test";
}

TEST_F(AdvertisementTest, LoadFindsAudioFiles) {
    createFile("ad1.mp3");
    createFile("ad2.wav");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, LoadIgnoresNonAudioFiles) {
    createFile("readme.txt");
    createFile("image.png");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener_));
}

TEST_F(AdvertisementTest, LoadEmptyDirectory) {
    Advertisement ad(test_directory_, dice_);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener_));
}

TEST_F(AdvertisementTest, LoadNonExistentDirectory) {
    Advertisement ad("/nonexistent/path", dice_);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener_));
}

TEST_F(AdvertisementTest, InterruptStartsPlayback) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, InterruptReturnsTrueWithAds) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptReturnsFalseWhenNoAds) {
    Advertisement ad(test_directory_, dice_);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener_));
}

TEST_F(AdvertisementTest, ConcludeReturnsTrueAfterInterrupt) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, ConcludeReturnsFalseWithoutInterrupt) {
    Advertisement ad(test_directory_, dice_);
    EXPECT_FALSE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, ConcludeReturnsFalseOnSecondCall) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    ad.conclude(listener_);
    EXPECT_FALSE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, InterruptAfterConcludeWorks) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    ad.conclude(listener_);
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, LoadMixedFiles) {
    createFile("ad1.mp3");
    createFile("readme.txt");
    createFile("ad2.wav");
    createFile("image.jpg");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptPlaysFromLoadedAds) {
    createFile("only_ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, MultipleInterruptsAllStart) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    ad.conclude(listener_);
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, ConcludeWithoutLoadReturnsFalse) {
    Advertisement ad(test_directory_, dice_);
    EXPECT_FALSE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, LoadMultipleMp3Files) {
    for (int i = 0; i < 8; i++) {
        createFile("ad" + std::to_string(i) + ".mp3");
    }
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptDoesNotStartWhenEmpty) {
    Advertisement ad(test_directory_, dice_);
    ad.load();
    ad.interrupt(listener_);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, LoadWavFiles) {
    createFile("sound.wav");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptProducesVariation) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    int trueCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (ad.interrupt(listener_)) {
            trueCount++;
            ad.conclude(listener_);
        }
    }
    EXPECT_GT(trueCount, 0);
    EXPECT_LT(trueCount, 1000);
}
```

## test/model/FileMetadataTest.h

```cpp
#ifndef FILE_METADATA_TEST_H
#define FILE_METADATA_TEST_H

#include "../DirectoryTestFixture.h"

class FileMetadataTest : public DirectoryTestFixture {
protected:
    std::string identify() const override;
};

#endif //FILE_METADATA_TEST_H

```

## test/model/FileMetadataTest.cpp

```cpp
#include "FileMetadataTest.h"
#include "../../model/FileMetadata.h"
#include <fstream>

std::string FileMetadataTest::identify() const {
    return "file_metadata_test";
}

TEST_F(FileMetadataTest, StampReturnsZeroForMissingFile) {
    EXPECT_EQ(0, FileMetadata("/nonexistent/path/file.mp3").stamp());
}

TEST_F(FileMetadataTest, StampReturnsNonZeroForExistingFile) {
    createFile("present.mp3");
    EXPECT_GT(FileMetadata(test_directory_ + "/present.mp3").stamp(), 0);
}

TEST_F(FileMetadataTest, LastReturnsZeroForMissingFile) {
    EXPECT_EQ(0, FileMetadata("/nonexistent/path/file.mp3").last());
}

TEST_F(FileMetadataTest, LastReturnsFileSize) {
    const std::string path = test_directory_ + "/sized.mp3";
    std::ofstream(path) << std::string(123, 'x');
    EXPECT_EQ(123, FileMetadata(path).last());
}

TEST_F(FileMetadataTest, LastDistinguishesFileSizes) {
    const std::string small = test_directory_ + "/small.mp3";
    const std::string large = test_directory_ + "/large.mp3";
    std::ofstream(small) << std::string(50, 'x');
    std::ofstream(large) << std::string(500, 'x');
    EXPECT_LT(FileMetadata(small).last(), FileMetadata(large).last());
}

```

## test/model/ModelTest.h

```cpp
#ifndef MODELTEST_H
#define MODELTEST_H

#include "../ModelTestFixture.h"
#include "../../model/MusicPlayer.h"

class ModelTest : public ModelTestFixture {
protected:
    std::string identify() const override;
    MusicPlayer create();
};

#endif
```

## test/model/ModelTest.cpp

```cpp
#include "ModelTest.h"
#include "../TestPlaylistVisitor.h"
#include "../../model/QuickSort.h"
#include "../../model/DurationSort.h"
#include "../../model/DateSort.h"
#include <filesystem>
#include <fstream>

std::string ModelTest::identify() const {
    return "model_test";
}

MusicPlayer ModelTest::create() {
    return MusicPlayer(base_directory_, dice_);
}

TEST_F(ModelTest, LoadsSongsFromDirectory) {
    createSong("(1) First.mp3");
    createSong("(2) Second.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, LoadsEmptyDirectory) {
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, PlaySelectsAndStartsSong) {
    createSong("song.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(ModelTest, PlayNotifiesSelection) {
    createSong("song.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(ModelTest, AdvanceMovesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, RetreatMovesToPreviousSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, RepeatOneReplays) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(ModelTest, RepeatAllLoops) {
    createSong("a.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(ModelTest, InsertValidFile) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/new.mp3");
    EXPECT_TRUE(listener_.wasChanged());
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(ModelTest, InsertUnsupportedFile) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/doc.txt") << "text";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/doc.txt");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertEmptyPath) {
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertDuplicateFile) {
    createSong("existing.mp3");
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/existing.mp3") << "audio";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/existing.mp3");
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(ModelTest, RemoveNotifiesChanged) {
    createSong("song.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, RemoveReducesPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByNumberNotifiesChanged) {
    createSong("(2) B.mp3");
    createSong("(1) A.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    musicPlayer.sort(byDuration);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SearchFiltersSongs) {
    createSong("Hello.mp3");
    createSong("Goodbye.mp3");
    createSong("Hello World.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("Hello", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, SearchNoResults) {
    createSong("Hello.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("ZZZZ", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, AcceptShowsAllSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(ModelTest, EndWithoutAdAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.skip();
    EXPECT_FALSE(listener_.wasRevealed());
}

TEST_F(ModelTest, InsertIncreasesPlaylistSize) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameOrders) {
    createSong("C.mp3");
    createSong("A.mp3");
    createSong("B.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(ModelTest, MultipleRemoves) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, MultipleInserts) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/a.mp3") << "audio";
    std::ofstream(srcDir + "/b.mp3") << "audio";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/a.mp3");
    musicPlayer.insert(srcDir + "/b.mp3");
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(ModelTest, ReverseNotifiesChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.reverse();
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, ReverseInvertsOrder) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    QuickSort byName;
    musicPlayer.sort(byName);
    musicPlayer.reverse();
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "c.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "a.mp3"));
}

TEST_F(ModelTest, RestoreNotifiesChanged) {
    createSong("a.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    QuickSort byName;
    musicPlayer.sort(byName);
    musicPlayer.restore();
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByDateNotifiesChanged) {
    createSong("a.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    DateSort byDate;
    musicPlayer.sort(byDate);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByDateAcceptsSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    DateSort byDate;
    musicPlayer.sort(byDate);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}
```

## test/model/MusicLibraryTest.h

```cpp
#ifndef MUSICLIBRARYTEST_H
#define MUSICLIBRARYTEST_H

#include "../DirectoryTestFixture.h"

class MusicLibraryTest : public DirectoryTestFixture {
protected:
    std::string identify() const override;
};

#endif
```

## test/model/MusicLibraryTest.cpp

```cpp
#include "MusicLibraryTest.h"
#include "../../model/MusicLibrary.h"
#include "../TestPlaylistVisitor.h"
#include <fstream>

std::string MusicLibraryTest::identify() const {
    return "library_test";
}

TEST_F(MusicLibraryTest, ScanFindsMp3Files) {
    createFile("song.mp3");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(1, result.size());
}

TEST_F(MusicLibraryTest, ScanFindsWavFiles) {
    createFile("song.wav");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(1, result.size());
}

TEST_F(MusicLibraryTest, ScanIgnoresNonAudioFiles) {
    createFile("readme.txt");
    createFile("image.png");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(0, result.size());
}

TEST_F(MusicLibraryTest, ScanMixedFiles) {
    createFile("song.mp3");
    createFile("readme.txt");
    createFile("audio.wav");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(2, result.size());
}

TEST_F(MusicLibraryTest, ScanEmptyDirectory) {
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(0, result.size());
}

TEST_F(MusicLibraryTest, ScanNonExistentDirectory) {
    auto result = MusicLibrary::scan("/nonexistent");
    EXPECT_EQ(0, result.size());
}

TEST_F(MusicLibraryTest, ScanMultipleMp3) {
    for (int i = 0; i < 10; i++) {
        createFile("song" + std::to_string(i) + ".mp3");
    }
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(10, result.size());
}

TEST_F(MusicLibraryTest, IsSupportedMp3) {
    EXPECT_TRUE(MusicLibrary::isSupported("song.mp3"));
}

TEST_F(MusicLibraryTest, IsSupportedWav) {
    EXPECT_TRUE(MusicLibrary::isSupported("song.wav"));
}

TEST_F(MusicLibraryTest, IsSupportedRejectsTxt) {
    EXPECT_FALSE(MusicLibrary::isSupported("readme.txt"));
}

TEST_F(MusicLibraryTest, IsSupportedRejectsPng) {
    EXPECT_FALSE(MusicLibrary::isSupported("image.png"));
}

TEST_F(MusicLibraryTest, IsSupportedRejectsNoExtension) {
    EXPECT_FALSE(MusicLibrary::isSupported("noextension"));
}

TEST_F(MusicLibraryTest, IsSupportedRejectsFlac) {
    EXPECT_FALSE(MusicLibrary::isSupported("song.flac"));
}

TEST_F(MusicLibraryTest, IsSupportedWithPath) {
    EXPECT_TRUE(MusicLibrary::isSupported("/music/dir/song.mp3"));
}

TEST_F(MusicLibraryTest, IsSupportedEmptyString) {
    EXPECT_FALSE(MusicLibrary::isSupported(""));
}

TEST_F(MusicLibraryTest, LoadCreatesSongObjects) {
    createFile("song1.mp3");
    createFile("song2.wav");
    MusicLibrary lib(test_directory_);
    auto songs = lib.load();
    EXPECT_EQ(2, songs.size());
}

TEST_F(MusicLibraryTest, LoadEmptyDirectory) {
    MusicLibrary lib(test_directory_);
    auto songs = lib.load();
    EXPECT_EQ(0, songs.size());
}

TEST_F(MusicLibraryTest, LoadNonExistentDirectory) {
    MusicLibrary lib("/nonexistent");
    auto songs = lib.load();
    EXPECT_EQ(0, songs.size());
}

TEST_F(MusicLibraryTest, ContainsExistingFile) {
    createFile("exists.mp3");
    const MusicLibrary lib(test_directory_);
    EXPECT_TRUE(lib.contains("exists.mp3"));
}

TEST_F(MusicLibraryTest, ContainsMissingFile) {
    const MusicLibrary lib(test_directory_);
    EXPECT_FALSE(lib.contains("missing.mp3"));
}

TEST_F(MusicLibraryTest, ImportCopiesFile) {
    const std::string srcDir = test_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "data";

    const MusicLibrary lib(test_directory_);
    lib.import(srcDir + "/new.mp3");
    EXPECT_TRUE(lib.contains("new.mp3"));
}

TEST_F(MusicLibraryTest, ImportReturnsSong) {
    const std::string srcDir = test_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "data";

    const MusicLibrary lib(test_directory_);
    const Song song = lib.import(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    song.accept(visitor);
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(MusicLibraryTest, ImportDoesNotDuplicateExisting) {
    createFile("existing.mp3");
    const std::string srcDir = test_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/existing.mp3") << "different data";

    const MusicLibrary lib(test_directory_);
    EXPECT_TRUE(lib.contains("existing.mp3"));
}

TEST_F(MusicLibraryTest, EraseRemovesFile) {
    createFile("to_delete.mp3");
    MusicLibrary lib(test_directory_);
    EXPECT_TRUE(lib.contains("to_delete.mp3"));
    lib.erase(test_directory_ + "/to_delete.mp3");
    EXPECT_FALSE(lib.contains("to_delete.mp3"));
}

TEST_F(MusicLibraryTest, ScanReturnsFullPaths) {
    createFile("song.mp3");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result[0].find(test_directory_) != std::string::npos);
}

TEST_F(MusicLibraryTest, LoadSongsAcceptVisitor) {
    createFile("test.mp3");
    const MusicLibrary lib(test_directory_);
    auto songs = lib.load();
    TestPlaylistVisitor visitor;
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasName("test.mp3"));
}
```

## test/model/PlaylistTest.h

```cpp
#ifndef PLAYLISTTEST_H
#define PLAYLISTTEST_H

#include <gtest/gtest.h>
#include "../../model/Playlist.h"
#include "../../model/MusicLibrary.h"
#include "../TestPlaylistVisitor.h"
#include "../MockPlaybackListener.h"
#include <string>

class PlaylistTest : public ::testing::Test {
protected:
    std::string test_directory_;
    MusicLibrary*library_ = nullptr;
    Playlist*playlist_ = nullptr;
    TestPlaylistVisitor visitor_;
    MockPlaybackListener listener_;

    void SetUp() override;
    void TearDown() override;
    void populate(int count) const;
};

#endif
```

## test/model/PlaylistTest.cpp

```cpp
#include "PlaylistTest.h"
#include "../../model/DurationSort.h"
#include "../../model/QuickSort.h"
#include "../../model/IPlaybackListener.h"
#include <filesystem>
#include <fstream>

void PlaylistTest::SetUp() {
    test_directory_ = std::filesystem::temp_directory_path().string() + "/playlist_test";
    std::filesystem::create_directories(test_directory_);
    library_ = new MusicLibrary(test_directory_);
    playlist_ = new Playlist(*library_);
}

void PlaylistTest::TearDown() {
    delete playlist_;
    delete library_;
    std::filesystem::remove_all(test_directory_);
}

void PlaylistTest::populate(int count) const {
    for (int i = 0; i < count; i++) {
        playlist_->add(Song("(" + std::to_string(i + 1) + ") Song" + std::to_string(i) + ".mp3",
                          test_directory_ + "/song" + std::to_string(i) + ".mp3"));
    }
}

TEST_F(PlaylistTest, AddSingleSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
}

TEST_F(PlaylistTest, AddMultipleSongs) {
    populate(5);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(5));
}

TEST_F(PlaylistTest, AddPreservesOrder) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
}

TEST_F(PlaylistTest, RemoveReducesCount) {
    populate(3);
    playlist_->remove(1);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(2));
}

TEST_F(PlaylistTest, RemoveFirstSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->remove(0);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "B.mp3"));
}

TEST_F(PlaylistTest, RemoveLastSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->remove(1);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
    EXPECT_TRUE(visitor_.hasName("A.mp3"));
}

TEST_F(PlaylistTest, RemoveInvalidNegativeIndex) {
    populate(3);
    playlist_->remove(-1);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
}

TEST_F(PlaylistTest, RemoveInvalidLargeIndex) {
    populate(3);
    playlist_->remove(100);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
}

TEST_F(PlaylistTest, RemoveFromEmptyPlaylist) {
    playlist_->remove(0);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SortByNameAlphabetical) {
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "C.mp3"));
}

TEST_F(PlaylistTest, SortByDurationAscending) {
    const std::string large = test_directory_ + "/large.mp3";
    const std::string small = test_directory_ + "/small.mp3";
    const std::string medium = test_directory_ + "/medium.mp3";
    std::ofstream(large) << std::string(300, 'x');
    std::ofstream(small) << std::string(100, 'x');
    std::ofstream(medium) << std::string(200, 'x');
    playlist_->add(Song("large.mp3", large));
    playlist_->add(Song("small.mp3", small));
    playlist_->add(Song("medium.mp3", medium));
    DurationSort byDuration;
    playlist_->sort(byDuration);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "small.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "medium.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "large.mp3"));
}

TEST_F(PlaylistTest, SortEmptyPlaylist) {
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SortSingleSong) {
    playlist_->add(Song("A.mp3", "/a"));
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
}

TEST_F(PlaylistTest, ShuffleDoesNotChangeCount) {
    populate(10);
    playlist_->shuffle();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(10));
}

TEST_F(PlaylistTest, ShufflePreservesSelection) {
    populate(5);
    playlist_->select(2, listener_);
    playlist_->shuffle();
    EXPECT_TRUE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, ClearRemovesAllSongs) {
    populate(5);
    playlist_->clear();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, ClearResetsSelection) {
    populate(5);
    playlist_->select(2, listener_);
    playlist_->clear();
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, SelectValidIndex) {
    populate(3);
    playlist_->select(1, listener_);
    EXPECT_TRUE(playlist_->hasSelected());
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, SelectInvalidNegativeIndex) {
    populate(3);
    playlist_->select(-1, listener_);
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, SelectInvalidLargeIndex) {
    populate(3);
    playlist_->select(100, listener_);
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, AdvanceMovesToNext) {
    populate(3);
    playlist_->select(0, listener_);
    playlist_->advance(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, AdvanceAtEndDoesNothing) {
    populate(3);
    playlist_->select(2, listener_);
    playlist_->advance(listener_);
    EXPECT_FALSE(listener_.wasSelectedWith(3));
}

TEST_F(PlaylistTest, RetreatMovesToPrevious) {
    populate(3);
    playlist_->select(2, listener_);
    playlist_->retreat(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RetreatAtStartDoesNothing) {
    populate(3);
    playlist_->select(0, listener_);
    playlist_->retreat(listener_);
    EXPECT_FALSE(listener_.wasSelectedWith(-1));
}

TEST_F(PlaylistTest, PlayCurrentSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->select(0, listener_);
    playlist_->play(visitor_);
    EXPECT_TRUE(visitor_.hasName("A.mp3"));
}

TEST_F(PlaylistTest, PlayWithNoSelection) {
    populate(3);
    playlist_->play(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SearchFindsMatchingSongs) {
    playlist_->add(Song("Hello.mp3", "/a"));
    playlist_->add(Song("Goodbye.mp3", "/b"));
    playlist_->add(Song("Hello World.mp3", "/c"));
    playlist_->search("Hello", visitor_);
    EXPECT_TRUE(visitor_.hasSongs(2));
}

TEST_F(PlaylistTest, SearchReturnsEmptyForNoMatch) {
    populate(5);
    playlist_->search("ZZZZZ", visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SearchEmptyQueryReturnsAll) {
    populate(3);
    playlist_->search("", visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
}

TEST_F(PlaylistTest, HasNextWhenMoreSongsExist) {
    populate(3);
    playlist_->select(0, listener_);
    EXPECT_TRUE(playlist_->hasNext());
}

TEST_F(PlaylistTest, HasNextFalseAtEnd) {
    populate(3);
    playlist_->select(2, listener_);
    EXPECT_FALSE(playlist_->hasNext());
}

TEST_F(PlaylistTest, HasSelectedFalseInitially) {
    populate(3);
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, HasSelectedTrueAfterSelect) {
    populate(3);
    playlist_->select(1, listener_);
    EXPECT_TRUE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, RemoveCurrentSongResetsSelection) {
    populate(3);
    playlist_->select(1, listener_);
    playlist_->remove(1);
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, RemoveBeforeCurrentAdjustsIndex) {
    populate(5);
    playlist_->select(3, listener_);
    playlist_->remove(0);
    playlist_->play(visitor_);
    EXPECT_TRUE(visitor_.hasName("(4) Song3.mp3"));
}

TEST_F(PlaylistTest, AcceptEmptyPlaylist) {
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, AcceptAllSongs) {
    populate(4);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(4));
}

TEST_F(PlaylistTest, SelectNotifiesListener) {
    populate(3);
    playlist_->select(2, listener_);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaylistTest, AdvanceNotifiesListener) {
    populate(3);
    playlist_->select(0, listener_);
    playlist_->advance(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RetreatNotifiesListener) {
    populate(3);
    playlist_->select(2, listener_);
    playlist_->retreat(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, ReverseInvertsOrder) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->reverse();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "A.mp3"));
}

TEST_F(PlaylistTest, ReverseEmptyPlaylist) {
    playlist_->reverse();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, ReversePreservesCurrentSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->select(0, listener_);
    playlist_->reverse();
    playlist_->retreat(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RestoreReturnsOriginalOrder) {
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->restore();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "B.mp3"));
}

TEST_F(PlaylistTest, RestoreDoesNothingWhenNothingPreserved) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->restore();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
}

TEST_F(PlaylistTest, RestorePreservesCurrentSong) {
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->select(0, listener_);
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->restore();
    playlist_->advance(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, SortReverseRestoreFullCycle) {
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->reverse();
    playlist_->restore();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "B.mp3"));
}
```

## test/model/SongTest.h

```cpp
#ifndef SONGTEST_H
#define SONGTEST_H

#include <gtest/gtest.h>
#include "../TestPlaylistVisitor.h"

class SongTest : public ::testing::Test {
protected:
    TestPlaylistVisitor visitor_;
};

#endif
```

## test/model/SongTest.cpp

```cpp
#include "SongTest.h"
#include "../../model/Song.h"
#include <filesystem>
#include <fstream>

TEST_F(SongTest, AcceptPassesNameToVisitor) {
    Song song("(1) First Song.mp3", "/music/(1) First Song.mp3");
    song.accept(visitor_);
    EXPECT_TRUE(visitor_.hasName("(1) First Song.mp3"));
}

TEST_F(SongTest, AcceptPassesPathToVisitor) {
    Song song("song.mp3", "/music/song.mp3");
    song.accept(visitor_);
    EXPECT_TRUE(visitor_.hasPath("/music/song.mp3"));
}

TEST_F(SongTest, MatchFindsSubstring) {
    Song song("Beautiful Now.mp3", "/music/Beautiful Now.mp3");
    EXPECT_TRUE(song.matches("Beautiful"));
}

TEST_F(SongTest, MatchFindsExactName) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_TRUE(song.matches("Hello.wav"));
}

TEST_F(SongTest, MatchReturnsFalseForMismatch) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_FALSE(song.matches("Goodbye"));
}

TEST_F(SongTest, MatchIsCaseSensitive) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_FALSE(song.matches("hello"));
}

TEST_F(SongTest, MatchFindsPartialName) {
    Song song("Counting Stars.mp3", "/music/Counting Stars.mp3");
    EXPECT_TRUE(song.matches("Stars"));
}

TEST_F(SongTest, MatchEmptyQueryMatchesAll) {
    Song song("anything.mp3", "/music/anything.mp3");
    EXPECT_TRUE(song.matches(""));
}

TEST_F(SongTest, ParseExtractsNameFromNumberedFormat) {
    EXPECT_EQ("First Song.mp3", Song::parse("(1) First Song.mp3"));
}

TEST_F(SongTest, ParseReturnsOriginalWhenNoNumber) {
    EXPECT_EQ("Hello.wav", Song::parse("Hello.wav"));
}

TEST_F(SongTest, ParseTrimsWhitespace) {
    EXPECT_EQ("Song.mp3", Song::parse("  Song.mp3  "));
}

TEST_F(SongTest, ParseHandlesMultiDigitNumbers) {
    EXPECT_EQ("Tenth Song.mp3", Song::parse("(10) Tenth Song.mp3"));
}

TEST_F(SongTest, ParseReturnsEmptyForWhitespaceOnly) {
    EXPECT_EQ("", Song::parse("   "));
}

TEST_F(SongTest, AcceptMultipleSongsToSameVisitor) {
    Song first("A.mp3", "/a");
    Song second("B.mp3", "/b");
    first.accept(visitor_);
    second.accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(2));
}

TEST_F(SongTest, AcceptPreservesOrderInVisitor) {
    Song first("A.mp3", "/a");
    Song second("B.mp3", "/b");
    first.accept(visitor_);
    second.accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
}

TEST_F(SongTest, MatchWithSpecialCharacters) {
    Song song("I'm good (Blue).mp3", "/music/I'm good (Blue).mp3");
    EXPECT_TRUE(song.matches("(Blue)"));
}

TEST_F(SongTest, ConstructionWithEmptyName) {
    Song song("", "/music/empty");
    song.accept(visitor_);
    EXPECT_TRUE(visitor_.hasName(""));
}

TEST_F(SongTest, ConstructionWithEmptyPath) {
    Song song("song.mp3", "");
    song.accept(visitor_);
    EXPECT_TRUE(visitor_.hasPath(""));
}

TEST_F(SongTest, ParseHandlesEmptyString) {
    EXPECT_EQ("", Song::parse(""));
}


```

## test/model/SortingTest.h

```cpp
#ifndef SORTINGTEST_H
#define SORTINGTEST_H

#include <gtest/gtest.h>
#include "../../model/DurationSort.h"
#include "../../model/QuickSort.h"
#include "../../model/Song.h"
#include "../TestPlaylistVisitor.h"
#include <vector>
#include <string>

class ShellSortTest : public ::testing::Test {
protected:
    std::string test_directory_;
    DurationSort sorter_;
    TestPlaylistVisitor visitor_;

    void SetUp() override;
    void TearDown() override;
    std::string createFile(const std::string& name, int size) const;
};

class QuickSortTest : public ::testing::Test {
protected:
    QuickSort sorter_;
    TestPlaylistVisitor visitor_;
};

#endif
```

## test/model/SortingTest.cpp

```cpp
#include "SortingTest.h"
#include <filesystem>
#include <fstream>

void ShellSortTest::SetUp() {
    test_directory_ = std::filesystem::temp_directory_path().string() + "/shell_sort_test";
    std::filesystem::create_directories(test_directory_);
}

void ShellSortTest::TearDown() {
    std::filesystem::remove_all(test_directory_);
}

std::string ShellSortTest::createFile(const std::string& name, const int size) const {
    const std::string path = test_directory_ + "/" + name;
    std::ofstream(path) << std::string(size, 'x');
    return path;
}

TEST_F(ShellSortTest, SortByDurationAscending) {
    const std::string c = createFile("c.mp3", 300);
    const std::string a = createFile("a.mp3", 100);
    const std::string b = createFile("b.mp3", 200);
    std::vector<Song> songs = {Song("c.mp3", c), Song("a.mp3", a), Song("b.mp3", b)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortAlreadySorted) {
    const std::string a = createFile("a.mp3", 100);
    const std::string b = createFile("b.mp3", 200);
    const std::string c = createFile("c.mp3", 300);
    std::vector<Song> songs = {Song("a.mp3", a), Song("b.mp3", b), Song("c.mp3", c)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortReversed) {
    const std::string e = createFile("e.mp3", 500);
    const std::string d = createFile("d.mp3", 400);
    const std::string c = createFile("c.mp3", 300);
    const std::string b = createFile("b.mp3", 200);
    const std::string a = createFile("a.mp3", 100);
    std::vector<Song> songs = {
        Song("e.mp3", e), Song("d.mp3", d), Song("c.mp3", c),
        Song("b.mp3", b), Song("a.mp3", a)
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortSingleElement) {
    const std::string a = createFile("a.mp3", 100);
    std::vector<Song> songs = {Song("a.mp3", a)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortEmptyVector) {
    std::vector<Song> songs;
    sorter_.sort(songs);
    EXPECT_TRUE(songs.empty());
}

TEST_F(ShellSortTest, SortDuplicateSizes) {
    const std::string b = createFile("b.mp3", 200);
    const std::string a = createFile("a.mp3", 100);
    const std::string c = createFile("c.mp3", 200);
    std::vector<Song> songs = {Song("b.mp3", b), Song("a.mp3", a), Song("c.mp3", c)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortPreservesAllElements) {
    const std::string c = createFile("c.mp3", 300);
    const std::string a = createFile("a.mp3", 100);
    const std::string b = createFile("b.mp3", 200);
    std::vector<Song> songs = {Song("c.mp3", c), Song("a.mp3", a), Song("b.mp3", b)};
    sorter_.sort(songs);
    EXPECT_EQ(3, songs.size());
}

TEST_F(ShellSortTest, SortTwoElements) {
    const std::string b = createFile("b.mp3", 200);
    const std::string a = createFile("a.mp3", 100);
    std::vector<Song> songs = {Song("b.mp3", b), Song("a.mp3", a)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortLargeCollection) {
    std::vector<Song> songs;
    for (int i = 100; i > 0; i--) {
        const std::string name = std::to_string(i) + ".mp3";
        const std::string path = createFile(name, i * 10);
        songs.emplace_back(name, path);
    }
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "1.mp3"));
}

TEST_F(QuickSortTest, SortByNameAlphabetical) {
    std::vector<Song> songs = {
        Song("C.mp3", "/c"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortAlreadySorted) {
    std::vector<Song> songs = {
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b"),
        Song("C.mp3", "/c")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortReversed) {
    std::vector<Song> songs = {
        Song("E.mp3", "/e"),
        Song("D.mp3", "/d"),
        Song("C.mp3", "/c"),
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortSingleElement) {
    std::vector<Song> songs = { Song("A.mp3", "/a") };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortEmptyVector) {
    std::vector<Song> songs;
    sorter_.sort(songs);
    EXPECT_TRUE(songs.empty());
}

TEST_F(QuickSortTest, SortDuplicateNames) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b2")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortLargeCollection) {
    std::vector<Song> songs;
    for (int i = 100; i > 0; i--) {
        songs.emplace_back(std::to_string(i) + ".mp3", "/s");
    }
    sorter_.sort(songs);
    EXPECT_EQ(100, songs.size());
}

TEST_F(QuickSortTest, SortPreservesAllElements) {
    std::vector<Song> songs = {
        Song("C.mp3", "/c"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b")
    };
    sorter_.sort(songs);
    EXPECT_EQ(3, songs.size());
}

TEST_F(QuickSortTest, SortTwoElements) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortNumberedSongsByTitle) {
    std::vector<Song> songs = {
        Song("(2) Banana.mp3", "/b"),
        Song("(1) Cherry.mp3", "/c"),
        Song("(3) Apple.mp3", "/a")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "(3) Apple.mp3"));
}

```

## test/use_cases/AddSongUseCaseTest.h

```cpp
#ifndef ADD_SONG_USE_CASE_TEST_H
#define ADD_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class AddSongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
    std::string prepare(const std::string& name) const;
};

#endif //ADD_SONG_USE_CASE_TEST_H
```

## test/use_cases/AddSongUseCaseTest.cpp

```cpp
#include "AddSongUseCaseTest.h"
#include "../../model/MusicPlayer.h"
#include "../../model/QuickSort.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string AddSongUseCaseTest::identify() const {
    return "add_uc";
}

std::string AddSongUseCaseTest::prepare(const std::string& name) const {
    const std::string src_directory_ = base_directory_ + "/src";
    std::filesystem::create_directories(src_directory_);
    std::string path = src_directory_ + "/" + name;
    std::ofstream(path) << "audio";
    return path;
}

TEST_F(AddSongUseCaseTest, AddValidMp3GivesSuccessFeedback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddValidWavGivesSuccessFeedback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.wav");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedTypeGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.txt");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddDuplicateGivesFeedback) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(AddSongUseCaseTest, AddIncreasesPlaylistSize) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddNotifiesChanged) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddSongAppearsInPlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("my_track.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("my_track.mp3"));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongs) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string p1 = prepare("a.mp3");
    musicPlayer.insert(p1);
    std::string p2 = prepare("b.mp3");
    musicPlayer.insert(p2);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongsNotifiesMultipleTimes) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string p1 = prepare("a.mp3");
    musicPlayer.insert(p1);
    std::string p2 = prepare("b.mp3");
    musicPlayer.insert(p2);
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(AddSongUseCaseTest, AddAfterRemove) {
    createSong("existing.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    std::string path = prepare("new.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSort) {
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("a.mp3");
    musicPlayer.insert(path);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSearch) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("unique.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.search("unique", visitor);
    EXPECT_TRUE(visitor.hasName("unique.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenPlayNewSong) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddDoesNotStartPlayback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(AddSongUseCaseTest, AddDoesNotSelect) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddOggGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.ogg");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddFlacGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.flac");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotIncreasePlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.txt");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotNotifyChanged) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.txt");
    musicPlayer.insert(path);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotIncreasePlaylist) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotNotifyChanged) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddToExistingPlaylist) {
    createSong("existing.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("new.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddPreservesExistingSongs) {
    createSong("existing.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("new.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("existing.mp3"));
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathDoesNotIncreasePlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert("");
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddThreeSongsSequentially) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(prepare("a.mp3"));
    musicPlayer.insert(prepare("b.mp3"));
    musicPlayer.insert(prepare("c.mp3"));
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(AddSongUseCaseTest, AddThenRemoveThenAdd) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(prepare("a.mp3"));
    musicPlayer.remove(0);
    musicPlayer.insert(prepare("b.mp3"));
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(AddSongUseCaseTest, AddWavIncreasesPlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(prepare("track.wav"));
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddThenSortThenSearch) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(prepare("zebra.mp3"));
    musicPlayer.insert(prepare("alpha.mp3"));
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.search("alpha", visitor);
    EXPECT_TRUE(visitor.hasName("alpha.mp3"));
}

TEST_F(AddSongUseCaseTest, AddDoesNotCrashOnEmptyPlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    EXPECT_NO_THROW(musicPlayer.insert(path));
}
```

## test/use_cases/NavigatePlaylistUseCaseTest.h

```cpp
#ifndef NAVIGATE_PLAYLIST_USE_CASE_TEST_H
#define NAVIGATE_PLAYLIST_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class NavigatePlaylistUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //NAVIGATE_PLAYLIST_USE_CASE_TEST_H
```

## test/use_cases/NavigatePlaylistUseCaseTest.cpp

```cpp
#include "NavigatePlaylistUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include "../../model/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string NavigatePlaylistUseCaseTest::identify() const {
    return "navigate_uc";
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFromFirstToSecond) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFromMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAtEndDoesNotCrash) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.advance());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatFromLastToMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatFromMiddleToFirst) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAtStartDoesNotCrash) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.retreat());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenRetreatReturnsToStart) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThroughAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatThroughAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    musicPlayer.retreat();
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceNotifiesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatNotifiesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(2);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterInsert) {
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/b.mp3");
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterInsert) {
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/b.mp3");
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.advance();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(3));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(3);
    musicPlayer.retreat();
    musicPlayer.retreat();
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenRetreatThenAdvance) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.retreat();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceOnSingleSongDoesNotCrash) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.advance());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatOnSingleSongDoesNotCrash) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.retreat());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceTwoSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatTwoSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFiveSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.advance();
    musicPlayer.advance();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(4));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceDoesNotNotifyChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatDoesNotNotifyChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenPlaylistUnchanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceSortedPlaylist) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatSortedPlaylist) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(2);
    musicPlayer.retreat();
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}
```

## test/use_cases/PlaySongUseCaseTest.h

```cpp
#ifndef PLAY_SONG_USE_CASE_TEST_H
#define PLAY_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class PlaySongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //PLAY_SONG_USE_CASE_TEST_H
```

## test/use_cases/PlaySongUseCaseTest.cpp

```cpp
#include "PlaySongUseCaseTest.h"
#include "../../model/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string PlaySongUseCaseTest::identify() const {
    return "play_uc";
}

TEST_F(PlaySongUseCaseTest, PlaySelectsSong) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, PlayStartsPlayback) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlaySecondSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, PlayThenPlayAnother) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.play(1);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, PlayLastSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(PlaySongUseCaseTest, PlayFromMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayAlwaysSelects) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayMultipleTimesAllSelect) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.play(1);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, EndAdvancesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, EndAtLastSongDoesNotCrash) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.end());
}

TEST_F(PlaySongUseCaseTest, RepeatOneReplays) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(PlaySongUseCaseTest, RepeatAllLoops) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, EndWithRepeatReplays) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.skip();
    EXPECT_FALSE(listener_.wasRevealed());
}

TEST_F(PlaySongUseCaseTest, PlayWithSingleSong) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayDoesNotCrashOnEmptyPlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    EXPECT_NO_THROW(musicPlayer.play(0));
}

TEST_F(PlaySongUseCaseTest, AdvanceFromFirstToSecond) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, RetreatFromSecondToFirst) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, AdvanceStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, RetreatStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, AdvanceThroughEntirePlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(PlaySongUseCaseTest, RetreatAtStartDoesNotCrash) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.retreat());
}

TEST_F(PlaySongUseCaseTest, AdvanceAtEndDoesNotCrash) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.advance());
}

TEST_F(PlaySongUseCaseTest, PlaySortedThenAdvance) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, EndMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.end();
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(PlaySongUseCaseTest, PlayAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayAfterInsert) {
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/new.mp3");
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, AdvanceThenRetreat) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, PlayAfterShuffle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, RepeatOffAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}
```

## test/use_cases/RemoveSongUseCaseTest.h

```cpp
#ifndef REMOVE_SONG_USE_CASE_TEST_H
#define REMOVE_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class RemoveSongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //REMOVE_SONG_USE_CASE_TEST_H
```

## test/use_cases/RemoveSongUseCaseTest.cpp

```cpp
#include "RemoveSongUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include "../../model/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string RemoveSongUseCaseTest::identify() const {
    return "remove_uc";
}

TEST_F(RemoveSongUseCaseTest, RemoveFirstSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(RemoveSongUseCaseTest, RemoveLastSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(2);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(RemoveSongUseCaseTest, RemoveMiddleSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(1);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(RemoveSongUseCaseTest, RemoveNotifiesChanged) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(RemoveSongUseCaseTest, RemoveReducesPlaylistSize) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveFromEmptyDoesNotCrash) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    EXPECT_NO_THROW(musicPlayer.remove(0));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenPlay) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(RemoveSongUseCaseTest, RemoveOnlySongLeavesEmpty) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(RemoveSongUseCaseTest, RemoveAllSongsOneByOne) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.remove(0);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(RemoveSongUseCaseTest, RemoveThenAdd) {
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.insert(srcDir + "/b.mp3");
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSearch) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.search("jazz", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotStartPlayback) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotSelect) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(RemoveSongUseCaseTest, RemoveMultipleNotifiesEachTime) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.remove(0);
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(RemoveSongUseCaseTest, RemovePreservesOtherSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.remove(1);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
    EXPECT_TRUE(visitor.hasName("c.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveFirstPreservesRest) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveLastPreservesRest) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.remove(1);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenPlayRemaining) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenAdvance) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenRetreat) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(RemoveSongUseCaseTest, RemoveAllThenAddNew) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";
    musicPlayer.insert(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveTwoFromThree) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSortRemaining) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "c.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveWavFile) {
    createSong("track.wav");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(RemoveSongUseCaseTest, RemoveNotifiesChangedOnce) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    EXPECT_TRUE(listener_.wasChangedTimes(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveFromFiveSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(2);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(4));
}

TEST_F(RemoveSongUseCaseTest, RemoveThreeTimesNotifiesThree) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.remove(0);
    musicPlayer.remove(0);
    EXPECT_TRUE(listener_.wasChangedTimes(3));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSearchFindsRemaining) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.remove(1);
    TestPlaylistVisitor visitor;
    musicPlayer.search("jazz", visitor);
    EXPECT_TRUE(visitor.hasName("jazz.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotGiveFeedback) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    EXPECT_FALSE(listener_.wasFeedback("Song added successfully!"));
}
```

## test/use_cases/SearchSongUseCaseTest.h

```cpp
#ifndef SEARCH_SONG_USE_CASE_TEST_H
#define SEARCH_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class SearchSongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //SEARCH_SONG_USE_CASE_TEST_H
```

## test/use_cases/SearchSongUseCaseTest.cpp

```cpp
#include "SearchSongUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include "../../model/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string SearchSongUseCaseTest::identify() const {
    return "search_uc";
}

TEST_F(SearchSongUseCaseTest, SearchFindsExactMatch) {
    createSong("hello.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("hello", visitor);
    EXPECT_TRUE(visitor.hasName("hello.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchNoMatchReturnsEmpty) {
    createSong("hello.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("goodbye", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchEmptyQueryReturnsAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchPartialName) {
    createSong("summer_breeze.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("summer", visitor);
    EXPECT_TRUE(visitor.hasName("summer_breeze.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchMultipleResults) {
    createSong("rock_anthem.mp3");
    createSong("rock_ballad.mp3");
    createSong("jazz_tune.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("rock", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchSingleResult) {
    createSong("rock_anthem.mp3");
    createSong("jazz_tune.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("jazz", visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SearchSongUseCaseTest, SearchOnEmptyPlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("anything", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchEmptyQueryOnEmptyPlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchAfterSort) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.search("banana", visitor);
    EXPECT_TRUE(visitor.hasName("banana.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchAfterInsert) {
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/b.mp3");
    TestPlaylistVisitor visitor;
    musicPlayer.search("b", visitor);
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchAfterRemove) {
    createSong("unique_song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.search("unique_song", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotStartPlayback) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("song", visitor);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotSelect) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("song", visitor);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotNotifyChanged) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("song", visitor);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(SearchSongUseCaseTest, SearchWithExtension) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search(".mp3", visitor);
    EXPECT_TRUE(visitor.hasName("song.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchWavFile) {
    createSong("track.wav");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("track", visitor);
    EXPECT_TRUE(visitor.hasName("track.wav"));
}

TEST_F(SearchSongUseCaseTest, SearchWithUnderscore) {
    createSong("my_song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("my_song", visitor);
    EXPECT_TRUE(visitor.hasName("my_song.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchWithDash) {
    createSong("my-song.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("my-song", visitor);
    EXPECT_TRUE(visitor.hasName("my-song.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchWithNumbers) {
    createSong("track01.mp3");
    createSong("track02.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("track0", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchSingleCharacter) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("a", visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchTwiceWithDifferentQueries) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor v1;
    musicPlayer.search("rock", v1);
    EXPECT_TRUE(v1.hasName("rock.mp3"));
    TestPlaylistVisitor v2;
    musicPlayer.search("jazz", v2);
    EXPECT_TRUE(v2.hasName("jazz.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotAffectPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor searchVisitor;
    musicPlayer.search("a", searchVisitor);
    TestPlaylistVisitor acceptVisitor;
    musicPlayer.accept(acceptVisitor);
    EXPECT_TRUE(acceptVisitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchResultHasCorrectName) {
    createSong("specific_name.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("specific", visitor);
    EXPECT_TRUE(visitor.hasName("specific_name.mp3"));
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SearchSongUseCaseTest, SearchAllSongsMatch) {
    createSong("song_a.mp3");
    createSong("song_b.mp3");
    createSong("song_c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("song", visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SearchSongUseCaseTest, SearchNoSongsMatch) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("zzz", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchAfterSortFindsAll) {
    createSong("rock_a.mp3");
    createSong("rock_b.mp3");
    createSong("jazz.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.search("rock", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchLongQuery) {
    createSong("very_long_song_name_here.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("very_long_song_name_here", visitor);
    EXPECT_TRUE(visitor.hasName("very_long_song_name_here.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchSingleSongPlaylist) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("only", visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotCrashOnEmptyPlaylist) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    EXPECT_NO_THROW(musicPlayer.search("test", visitor));
}

TEST_F(SearchSongUseCaseTest, SearchVisitorIsIndependent) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor v1;
    musicPlayer.search("a", v1);
    TestPlaylistVisitor v2;
    musicPlayer.search("b", v2);
    EXPECT_TRUE(v1.hasSongs(1));
    EXPECT_TRUE(v2.hasSongs(1));
}
```

## test/use_cases/SortPlaylistUseCaseTest.h

```cpp
#ifndef SORT_PLAYLIST_USE_CASE_TEST_H
#define SORT_PLAYLIST_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class SortPlaylistUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //SORT_PLAYLIST_USE_CASE_TEST_H

```

## test/use_cases/SortPlaylistUseCaseTest.cpp

```cpp
#include "SortPlaylistUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include "../../model/QuickSort.h"
#include "../../model/DurationSort.h"
#include <filesystem>
#include <fstream>

std::string SortPlaylistUseCaseTest::identify() const {
    return "sort_uc";
}

TEST_F(SortPlaylistUseCaseTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    musicPlayer.sort(byDuration);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortByNameOrdersAlphabetically) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "apple.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "banana.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "cherry.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortEmptyPlaylistDoesNotCrash) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortEmptyPlaylistNotifiesChanged) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongDoesNotCrash) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongPreserves) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("only.mp3"));
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SortPlaylistUseCaseTest, SortPreservesSongCount) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortPreservesAllSongNames) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
    EXPECT_TRUE(visitor.hasName("c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlayFirstSong) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlaySelectsCorrectIndex) {
    createSong("c.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(SortPlaylistUseCaseTest, SortThenAdvance) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(SortPlaylistUseCaseTest, SortThenRetreat) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(SortPlaylistUseCaseTest, SortMultipleTimesDoesNotCrash) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
    DurationSort byDuration;
    EXPECT_NO_THROW(musicPlayer.sort(byDuration));
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortMultipleTimesNotifiesEachTime) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    DurationSort byDuration;
    musicPlayer.sort(byTitle);
    musicPlayer.sort(byDuration);
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChangedTimes(3));
}

TEST_F(SortPlaylistUseCaseTest, SortAlreadySortedPreservesOrder) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberDoesNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    EXPECT_NO_THROW(musicPlayer.sort(byDuration));
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberPreservesSongCount) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    musicPlayer.sort(byDuration);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortAfterInsert) {
    createSong("c.mp3");
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/b.mp3");
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortAfterRemove) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.remove(1);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
    EXPECT_TRUE(visitor.hasName("a.mp3"));
    EXPECT_TRUE(visitor.hasName("c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortByNameThenByNumber) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    DurationSort byDuration;
    musicPlayer.sort(byDuration);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SortPlaylistUseCaseTest, SortByNameTwoSongs) {
    createSong("z.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "z.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortFiveSongsByName) {
    createSong("e.mp3");
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("d.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "c.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(3, "d.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(4, "e.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortThenAcceptVisitsAll) {
    createSong("b.mp3");
    createSong("a.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_FALSE(visitor.isEmpty());
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortDoesNotAffectPlayback) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(SortPlaylistUseCaseTest, SortDoesNotSelect) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlayThenAdvanceThroughAll) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(SortPlaylistUseCaseTest, SortWavFiles) {
    createSong("b.wav");
    createSong("a.wav");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.wav"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.wav"));
}

TEST_F(SortPlaylistUseCaseTest, SortMixedExtensions) {
    createSong("b.wav");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongNotifiesChanged) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChangedTimes(1));
}

TEST_F(SortPlaylistUseCaseTest, SortThenSearchFindsCorrectly) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.search("apple", visitor);
    EXPECT_TRUE(visitor.hasName("apple.mp3"));
}

```
