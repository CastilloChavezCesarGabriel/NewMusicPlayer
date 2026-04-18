#include "QtAdTimer.h"

QtAdTimer::QtAdTimer(QObject* parent) : QObject(parent) {
    timer_ = new QTimer(this);
    timer_->setSingleShot(true);
    connect(timer_, &QTimer::timeout, this, &QtAdTimer::revealRequested);
}

void QtAdTimer::schedule(const int milliseconds) {
    timer_->stop();
    timer_->start(milliseconds);
}

void QtAdTimer::cancel() {
    timer_->stop();
}