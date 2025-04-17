#include "remotetest.hpp"
#include "ina238config.hpp"

#include <wiringPi.h>

float connectAndSenseVoltage(){
    digitalWrite(inaConfig::RELAY_PIN, LOW);
    float result = sensor->voltage();
    digitalWrite(inaConfig::RELAY_PIN, HIGH);
    delay(1);
    return result;
}

void saveRecordedMesuremants(struct tm* localTime, float &voltage){
    std::ofstream file("testResults.txt", std::ios::app);
    file << "Time";
    if(localTime->tm_hour < 10){
        file << "0";
    }
    file << localTime->tm_hour << '.';
    if (localTime->tm_min < 10)
    {
        file << "0";
    }
    file << localTime->tm_min << ": " << voltage << std::endl;
    file.close();
}