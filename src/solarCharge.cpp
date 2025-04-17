#include "solarCharge.hpp"
#include "ina238config.hpp"

#include <vector>
#include <ctime>
#include <fstream>
#include <unistd.h>

using namespace std::chrono;

void SolarCharge::runTest(){
    bool batteryFullFlag = false;
    time_t currentTime;
    struct tm *localTime;

    float voltage = 3;

    while(voltage >= 2.66){
        time(&currentTime);
        localTime = localtime(&currentTime);
        
        voltage = connectAndSenseVoltage();
        //std::cout << "Alerts: " << std::hex << sensor->getAlerts() << std::endl;
        saveRecordedMesuremants(localTime, voltage);
        sleep(3600);
    }
    
    system("python3 ./graphTestResult.py --sc");
}

void SolarCharge::runTest2(){
    bool batteryFullFlag = false;
    time_t currentTime;
    struct tm *localTime;

    float voltage = 3;

    while(voltage >= 2.66){
        time(&currentTime);
        localTime = localtime(&currentTime);
        
        voltage = connectAndSenseVoltage();
        //std::cout << "Alerts: " << std::hex << sensor->getAlerts() << std::endl;
        saveRecordedMesuremants(localTime, voltage);
        sleep(10);
    }
    
    system("python3 ./graphTestResult.py --sc");
}
