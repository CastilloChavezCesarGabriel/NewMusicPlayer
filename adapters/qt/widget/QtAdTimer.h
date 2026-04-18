#ifndef QT_AD_TIMER_H
#define QT_AD_TIMER_H

#include "../../../view/ITimingPanel.h"
#include <QTimer>

class QtAdTimer final : public QObject, public ITimingPanel {
    Q_OBJECT
private:
    QTimer* timer_;

public:
    explicit QtAdTimer(QObject* parent = nullptr);
    void schedule(int milliseconds) override;
    void cancel() override;

signals:
    void revealRequested();
};

#endif //QT_AD_TIMER_H