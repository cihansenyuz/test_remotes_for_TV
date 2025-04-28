#include "batteryChargeMonitoringTest.hpp"
#include "ina238config.hpp"
#include "testconfig.hpp"

#include <vector>
#include <ctime>
#include <fstream>
#include <unistd.h>

using namespace std::chrono;

void BatteryChargeMonitoringTest::runTest(){
    time_t currentTime;
    struct tm *localTime;

    float voltage = 3;

    while(voltage >= TestSettings::BCMT::batteryLowThreshold){
        time(&currentTime);
        localTime = localtime(&currentTime);
        
        voltage = connectAndSenseVoltage();
        //std::cout << "Alerts: " << std::hex << sensor->getAlerts() << std::endl;
        saveRecordedMesuremants(localTime, voltage);
        sleep(TestSettings::BCMT::sleepSeconds);
    }
    
    // system("python3 ./graphTestResult.py --sc");
}
