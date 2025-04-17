#include "remotetest.hpp"
#include "ina238config.hpp"

#include <wiringPi.h>
#include <fstream>
#include <unistd.h>

RemoteTest::RemoteTest(){
    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;

    sensor = new Ina238(inaConfig::DEVICE_ADDRESS, inaConfig::BUS_NUMBER);
    sensor->setShuntCal(inaConfig::SHUNT_RESISTANCE, inaConfig::MAX_CURRENT);

    pinMode(inaConfig::RELAY_PIN, OUTPUT);
    digitalWrite(inaConfig::RELAY_PIN, HIGH);
    sleep(1);
}

RemoteTest::~RemoteTest(){
    delete sensor;
}

float RemoteTest::connectAndSenseVoltage(){
    digitalWrite(inaConfig::RELAY_PIN, LOW);
    float result = sensor->voltage();
    digitalWrite(inaConfig::RELAY_PIN, HIGH);
    delay(1);
    return result;
}

void RemoteTest::saveRecordedMesuremants(struct tm* localTime, float &voltage){
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