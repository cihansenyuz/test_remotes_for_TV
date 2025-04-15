#pragma once

#include "ina238.hpp"
#include <wiringPi.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <unistd.h>

#define DEVICE_ADDRESS 0x40
#define BUS_NUMBER 1
#define RELAY_PIN 25    // wiringPi pin number
#define TEST_DURATION 

using namespace std::chrono;

class SolarCharge{
public:
    SolarCharge();
    ~SolarCharge();
    void runTest();
    void runTest2();

private:
    Ina238 *sensor;
    float connectAndSenseVoltage();
    void saveRecordedMesuremants(struct tm* localTime, float &voltage);
};

