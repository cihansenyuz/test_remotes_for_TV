#pragma once

#include "ina238.hpp"
#include "irManager.hpp"
#include "servoController.hpp"
#include <wiringPi.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <unistd.h>

#define TOTAL_TEST_NO 100000 // integer multiple of TEST_QUANTITY_TO_MEASURE
#define TEST_QUANTITY_TO_MEASURE 200
#define MEASUREMENT_QUANTITY_TO_SAVE 20
#define IR_DATA_SIZE 24
#define MIN_HEADER_DURATION 7800
#define MAX_HEADER_DURATION 8200

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
