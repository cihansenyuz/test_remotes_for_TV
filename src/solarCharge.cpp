#include "solarCharge.hpp"
#include "ina238config.hpp"
#include "testconfig.hpp"

#include <vector>
#include <ctime>
#include <fstream>
#include <unistd.h>

using namespace std::chrono;

void SolarCharge::runTest(){
    time_t currentTime;
    struct tm *localTime;

    float voltage = 3;

    while(voltage >= testconfig::solarcharge::BATT_LOW_THRESHOULD){
        time(&currentTime);
        localTime = localtime(&currentTime);
        
        voltage = connectAndSenseVoltage();
        //std::cout << "Alerts: " << std::hex << sensor->getAlerts() << std::endl;
        saveRecordedMesuremants(localTime, voltage);
        sleep(testconfig::solarcharge::SLEEP_SECONDS);
    }
    
    system("python3 ./graphTestResult.py --sc");
}
