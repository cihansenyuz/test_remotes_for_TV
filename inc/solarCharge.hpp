#pragma once

#include "ina238.hpp"

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

