#pragma once

#include "ina238.hpp"
#include "irManager.hpp"
#include "servoController.hpp"

class PushAndMeas{
public:
    PushAndMeas();
    ~PushAndMeas();
    void runTest();

private:
    Ina238 *sensor;
    IrManager *irManager;
    ServoController *servoController;

    float connectAndSenseVoltage();
    void saveRecordedMesuremants(struct tm* localTime, float &voltage, bool &batteryLowFlag);
};
