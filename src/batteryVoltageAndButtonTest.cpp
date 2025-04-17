#include "batteryVoltageAndButtonTest.hpp"
#include "ina238config.hpp"
#include "testconfig.hpp"

#include <wiringPi.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <unistd.h>

void BatteryVoltageAndButtonTest::runTest(){
    time_t currentTime;
    struct tm *localTime;

    while(timeOut != testconfig::BVABT::TEST_TIMEOUT_WHEN_LOW_BATT)
    {
        time(&currentTime);
        localTime = localtime(&currentTime);
        
        voltage = connectAndSenseVoltage();
        saveRecordedMesuremants(localTime, voltage);

        if (batteryLowFlag)
        {
            sleep(testconfig::BVABT::SLEEP_SECONDS_WHEN_LOW_BATT);
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
        else if(headerDurition > testconfig::IR::MIN_HEADER_DURATION && headerDurition < testconfig::IR::MAX_HEADER_DURATION){
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
            sleep(testconfig::BVABT::SLEEP_SECONDS_WHEN_HIGH_BATT);
            std::cout << "50 press completed...\n";
        }
    }

    system("python3 ./graphTestResult.py --pam");
}

BatteryVoltageAndButtonTest::BatteryVoltageAndButtonTest(){
    irManager = new IrManager(inaConfig::IR_PIN);
    servoController = new ServoController(inaConfig::SERVO_PIN);
}

BatteryVoltageAndButtonTest::~BatteryVoltageAndButtonTest(){
    delete irManager;
    delete servoController;
}

void BatteryVoltageAndButtonTest::saveRecordedMesuremants(struct tm* localTime, float &voltage){
        std::ofstream file(testconfig::TEST_RESULTS_FILE_NAME, std::ios::app);
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

