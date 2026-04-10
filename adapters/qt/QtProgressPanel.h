#ifndef QT_PROGRESS_PANEL_H
#define QT_PROGRESS_PANEL_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>

#include "IWidgetSetup.h"

class QtProgressPanel final : public QWidget, public IWidgetSetup {
    Q_OBJECT
private:
    QMediaPlayer& media_;
    QSlider* progress_bar_;
    QLabel* elapsed_time_;
    QLabel* total_time_;

    static QString format(qint64 milliseconds);

public:
    explicit QtProgressPanel(QMediaPlayer& media, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) const;
};

#endif //QT_PROGRESS_PANEL_H