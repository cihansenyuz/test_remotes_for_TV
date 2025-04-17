#pragma once

#include "remotetest.hpp"
#include "irManager.hpp"
#include "servoController.hpp"

#include <vector>

class IrSignalValidationTest : public RemoteTest {
public:
    IrSignalValidationTest();
    ~IrSignalValidationTest();
    void runTest();

private:
    IrManager* irManager;
    ServoController* servoController;
    int headerDurition = 0;
    int testNo = 1;
    int totalErrorHeader = 0;
    int totalErrorData = 0;
    int consecutiveErrorHeader = 0;
    int consecutiveErrorData = 0;
    std::vector<std::pair<int, float>> testResults;

    void saveRecordedMesuremants();
};