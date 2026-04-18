#ifndef QT_AUDIO_ENGINE_H
#define QT_AUDIO_ENGINE_H

#include "QtProgressPanel.h"
#include "IWidgetSetup.h"
#include "../../../view/IAudioPlayer.h"
#include "../../../view/ITimingPanel.h"
#include "../../../view/IEnableable.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <string>

class QtAudioEngine final : public QWidget, public IWidgetSetup, public IAudioPlayer, public ITimingPanel, public IEnableable {
    Q_OBJECT
private:
    QMediaPlayer* media_player_;
    QAudioOutput* audio_output_;
    QTimer* ad_timer_;
    QtProgressPanel* progress_bar_;

    void monitor();
    void start() const;
    void detect(QMediaPlayer::MediaStatus status);
    void announce(QMediaPlayer::PlaybackState state);
    void adopt() const;

public:
    explicit QtAudioEngine(QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void play(const std::string& path) override;
    void resume() override;
    void pause() override;
    void stop() override;
    void adjust(int volume) override;
    void schedule(int milliseconds) override;
    void cancel() override;
    void enable(bool state) override;

signals:
    void endRequested();
    void revealRequested();
    void toggleRequested(bool playing);
};

#endif //QT_AUDIO_ENGINE_H