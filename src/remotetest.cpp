#include "remotetest.hpp"
#include "ina238config.hpp"
#include "testconfig.hpp"

#include <wiringPi.h>
#include <fstream>
#include <unistd.h>

RemoteTest::RemoteTest(){
    if(wiringPiSetup())
        emit messageFeed("hata: wiringPi kurulumu hata verdi");
    else
        emit messageFeed("bilgi: wiringPi kurulumu başarılı");

    sensor = new Ina238(INA238Config::getInstance().getDeviceAddress(),
                        INA238Config::getInstance().getBusNumber());
    sensor->setShuntCal(INA238Config::getInstance().getShuntResistance(),
                        INA238Config::getInstance().getMaxCurrent());

    pinMode(INA238Config::getInstance().getRelayPin(), OUTPUT);
    digitalWrite(INA238Config::getInstance().getRelayPin(), HIGH);
    sleep(1);
}

RemoteTest::~RemoteTest(){
    delete sensor;
}

float RemoteTest::connectAndSenseVoltage(){
    digitalWrite(INA238Config::getInstance().getRelayPin(), LOW);
    delay(50);
    float calculated_voltage = sensor->voltage();
    digitalWrite(INA238Config::getInstance().getRelayPin(), HIGH);
    delay(50);
    return calculated_voltage;
}

void RemoteTest::saveRecordedMesuremants(struct tm* localTime, float &voltage){
    std::ofstream file(TestSettings::getInstance().testResultsFileName, std::ios::app);
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