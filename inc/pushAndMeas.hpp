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

    void saveRecordedMesuremants(struct tm* localTime, float &voltage) override;
};
