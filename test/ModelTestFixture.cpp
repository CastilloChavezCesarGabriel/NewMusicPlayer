#include "ModelTestFixture.h"
#include "../model/Song.h"
#include <filesystem>
#include <fstream>

void ModelTestFixture::SetUp() {
    base_directory_ = std::filesystem::temp_directory_path().string() + "/" + identify();
    music_directory_ = base_directory_ + "/music";
    ads_directory_ = base_directory_ + "/announcements";
    std::filesystem::create_directories(music_directory_);
    std::filesystem::create_directories(ads_directory_);
    notifier_.add(listener_);
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

void ModelTestFixture::build() {
    music_library_ = std::make_unique<MusicLibrary>(music_directory_);
    playlist_ = std::make_unique<Playlist>(*music_library_, notifier_);
    for (const Song& song : music_library_->load()) {
        playlist_->add(song);
    }
    playlist_->shuffle();

    advertisement_ = std::make_unique<Advertisement>(ads_directory_, dice_, notifier_);
    advertisement_->load();

    repeat_mode_ = std::make_unique<RepeatMode>(*playlist_, notifier_);

    playback_ = std::make_unique<Playback>(*playlist_, *advertisement_, *repeat_mode_);
    library_ = std::make_unique<Library>(*music_library_, *playlist_, notifier_);
    setlist_ = std::make_unique<Setlist>(*playlist_, notifier_);
    catalog_ = std::make_unique<Catalog>(*playlist_);
    repeat_switch_ = std::make_unique<RepeatSwitch>(*repeat_mode_);
}
