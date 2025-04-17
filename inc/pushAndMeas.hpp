#pragma once

#include "remotetest.hpp"
#include "irManager.hpp"
#include "servoController.hpp"

class PushAndMeas : public RemoteTest{
public:
    PushAndMeas();
    ~PushAndMeas() override;
    void runTest() override;

private:
    IrManager *irManager;
    ServoController *servoController;
    bool batteryLowFlag{false};
    int headerDurition = 0;
    short consecutiveErrorHeader = 0;
    int timeOut = 0;
    int buttonPress = 0;
    float voltage;

    void saveRecordedMesuremants(struct tm* localTime, float &voltage) override;
};
