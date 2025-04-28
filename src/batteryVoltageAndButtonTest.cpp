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

    while(timeOut != TestSettings::getInstance().BVABT.testTimeoutWhenLowBattery)
    {
        time(&currentTime);
        localTime = localtime(&currentTime);
        
        voltage = connectAndSenseVoltage();
        saveRecordedMesuremants(localTime, voltage);

        if (batteryLowFlag)
        {
            sleep(TestSettings::getInstance().BVABT.sleepSecondsWhenLowBattery);
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
        else if(headerDurition > TestSettings::getInstance().IR.minHeaderDuration
                && headerDurition < TestSettings::getInstance().IR.maxHeaderDuration){
            batteryLowFlag = false;
            consecutiveErrorHeader = 0;
        }
        else{
            std::cout << "Could not catch the header" << std::endl;
            consecutiveErrorHeader++;
            delete irManager;
            delay(200);
            irManager = new IrManager(INA238Config::getInstance().getIRPin());
            delay(1000);
        }
        
        buttonPress++;
        if (buttonPress == 50)
        {
            buttonPress = 0;
            sleep(TestSettings::getInstance().BVABT.sleepSecondsWhenHighBattery);
            std::cout << "50 press completed...\n";
        }
    }
    
    emit finished();
    //system("python3 ./graphTestResult.py --pam");
}

BatteryVoltageAndButtonTest::BatteryVoltageAndButtonTest(){
    irManager = new IrManager(INA238Config::getInstance().getIRPin());
    servoController = new ServoController(INA238Config::getInstance().getServoPin());
}

BatteryVoltageAndButtonTest::~BatteryVoltageAndButtonTest(){
    delete irManager;
    delete servoController;
}

void BatteryVoltageAndButtonTest::saveRecordedMesuremants(struct tm* localTime, float &voltage){
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
        file << localTime->tm_min << ": " << voltage << '\t';
        file << !batteryLowFlag << std::endl;
        file.close();
}

