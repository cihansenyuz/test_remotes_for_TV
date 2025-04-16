#pragma once

#include "ina238.hpp"
#include "irManager.hpp"
#include "servoController.hpp"

#include <vector>

#define TOTAL_TEST_NO 100000 // integer multiple of TEST_QUANTITY_TO_MEASURE
#define TEST_QUANTITY_TO_MEASURE 200
#define MEASUREMENT_QUANTITY_TO_SAVE 20
#define IR_DATA_SIZE 24
#define MIN_HEADER_DURATION 7800
#define MAX_HEADER_DURATION 8200

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