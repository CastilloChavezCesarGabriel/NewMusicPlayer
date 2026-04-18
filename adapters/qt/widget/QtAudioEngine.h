#ifndef QT_AUDIO_ENGINE_H
#define QT_AUDIO_ENGINE_H

#include "QtProgressPanel.h"
#include "IWidgetSetup.h"
#include "../../../view/IAudioPlayer.h"
#include "../../../view/IEnableable.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <string>

class QtAudioEngine final : public QWidget, public IWidgetSetup, public IAudioPlayer, public IEnableable {
    Q_OBJECT
private:
    QMediaPlayer* media_player_;
    QAudioOutput* audio_output_;
    QtProgressPanel* progress_bar_;

    void monitor();
    void start() const;
    void detect(QMediaPlayer::MediaStatus status);
    void announce(QMediaPlayer::PlaybackState state);
    void route() const;

public:
    explicit QtAudioEngine(QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void play(const std::string& path) override;
    void resume() override;
    void pause() override;
    void stop() override;
    void adjust(int volume) override;
    void enable(bool state) override;

signals:
    void endRequested();
    void toggleRequested(bool playing);
};

#endif //QT_AUDIO_ENGINE_H