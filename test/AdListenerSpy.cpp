#include "AdListenerSpy.h"
#include <gtest/gtest.h>

void AdListenerSpy::onEnable(bool) {}

void AdListenerSpy::onReveal(bool) {
    reveals_++;
}

void AdListenerSpy::onSchedule(int) {}
void AdListenerSpy::onCancel() {}

void AdListenerSpy::expectNoReveal() const {
    EXPECT_EQ(reveals_, 0) << "expected no onReveal, but got " << reveals_;
}