#pragma once

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