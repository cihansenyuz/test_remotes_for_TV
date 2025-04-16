#pragma once

#include "ina238.hpp"
#include "irManager.hpp"
#include "servoController.hpp"

#include <vector>

class SolarlessIrButtonClick{
public:
    SolarlessIrButtonClick();
    ~SolarlessIrButtonClick();
    void runTest();

private:
    Ina238* sensor;
    IrManager* irManager;
    ServoController* servoController;
    int testNo;
    int totalErrorHeader;
    int totalErrorData;
    int consecutiveErrorHeader;
    int consecutiveErrorData;

    float connectAndSenseVoltage();
    void saveRecordedMesuremants(std::vector<std::pair<int, float>>&);
};