#include "pushAndMeas.hpp"
#include "ina238config.hpp"
#include "testconfig.hpp"

#include <wiringPi.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <unistd.h>

void PushAndMeas::runTest(){
    int headerDurition = 0;
    short consecutiveErrorHeader = 0;
    int timeOut = 0;
    int buttonPress = 0;
    float voltage;
    time_t currentTime;
    struct tm *localTime;
    bool batteryLowFlag = false;

    while(timeOut != 24)
    {
        time(&currentTime);
        localTime = localtime(&currentTime);
        
        voltage = connectAndSenseVoltage();
        saveRecordedMesuremants(localTime, voltage, batteryLowFlag);

        if (batteryLowFlag)
        {
            sleep(900);
            timeOut++;
        }
        else
        {
            timeOut = 0;
        }

        delay(40);
        servoController->pressButton();
        headerDurition = irManager->waitForHeaderBits();
        servoController->releaseButton();

        if((consecutiveErrorHeader) == 3){
            std::cout << "Battery is low!\n";
            batteryLowFlag = true;
            buttonPress = 0;
            continue;
        }
        else if(headerDurition > testconfig::MIN_HEADER_DURATION && headerDurition < testconfig::MAX_HEADER_DURATION){
            batteryLowFlag = false;
            consecutiveErrorHeader = 0;
        }
        else{
            std::cout << "Could not catch the header" << std::endl;
            consecutiveErrorHeader++;
            delete irManager;
            delay(200);
            irManager = new IrManager(inaConfig::IR_PIN);
            delay(1000);
        }
        
        buttonPress++;
        if (buttonPress == 50)
        {
            buttonPress = 0;
            sleep(900);
            std::cout << "50 press completed...\n";
        }
    }

    delete sensor;
    delete irManager;
    delete servoController;
    system("python3 ./graphTestResult.py --pam");
}

PushAndMeas::PushAndMeas(){
    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;

    sensor = new Ina238(inaConfig::DEVICE_ADDRESS, inaConfig::BUS_NUMBER);
    sensor->setShuntCal(inaConfig::SHUNT_RESISTANCE, inaConfig::MAX_CURRENT);
    irManager = new IrManager(inaConfig::IR_PIN);
    servoController = new ServoController(inaConfig::SERVO_PIN);
    
    // Relay setup
    pinMode(inaConfig::RELAY_PIN, OUTPUT);
    digitalWrite(inaConfig::RELAY_PIN, HIGH);
}

PushAndMeas::~PushAndMeas(){
    delete sensor;
    delete irManager;
    delete servoController;
}

float PushAndMeas::connectAndSenseVoltage(){
    digitalWrite(inaConfig::RELAY_PIN, LOW);
    delay(50);
    float temp = sensor->voltage();
    digitalWrite(inaConfig::RELAY_PIN, HIGH);
    delay(50);
    return temp;
}

void PushAndMeas::saveRecordedMesuremants(struct tm* localTime, float &voltage, bool &batteryLowFlag){
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
        file << localTime->tm_min << ": " << voltage << '\t';
        file << !batteryLowFlag << std::endl;
        file.close();
}

