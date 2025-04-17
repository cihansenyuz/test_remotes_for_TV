#pragma once

#include "remotetest.hpp"
#include "irManager.hpp"
#include "servoController.hpp"

#include <vector>

class SolarlessIrButtonClick : public RemoteTest{
public:
    SolarlessIrButtonClick();
    ~SolarlessIrButtonClick();
    void runTest();

private:
    IrManager* irManager;
    ServoController* servoController;
    int testNo;
    int totalErrorHeader;
    int totalErrorData;
    int consecutiveErrorHeader;
    int consecutiveErrorData;

    void saveRecordedMesuremants(std::vector<std::pair<int, float>>&);
};