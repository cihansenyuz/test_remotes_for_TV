#pragma once

#include "remotetest.hpp"
#include "irSignalValidationTest.hpp"
#include "batteryChargeMonitoringTest.hpp"
#include "batteryVoltageAndButtonTest.hpp"

class TestFactory{
public:
    static RemoteTest* createTest(const QString &testName){
        if(testName == "IrSignalValidationTest"){
            return new IrSignalValidationTest;
        } else if(testName == "BatteryChargeMonitoringTest"){
            return new BatteryChargeMonitoringTest;
        } else if(testName == "BatteryVoltageAndButtonTest"){
            return new BatteryVoltageAndButtonTest;
        } else {
            return nullptr;
        }
    }
};