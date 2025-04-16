#include "solarlessIrButtonClick.hpp"
#include "ina238config.hpp"
#include "testconfig.hpp"

#include <fstream>
#include <wiringPi.h>
#include <stdio.h>

void SolarlessIrButtonClick::runTest()
{
    bool data[testconfig::IR_DATA_SIZE];
    std::vector<std::pair<int, float>> testResults;
    int headerDurition = 0;
    short totalErrorHeader = 0;
    short totalErrorData = 0;
    short consecutiveErrorHeader = 0;
    short consecutiveErrorData = 0;
    int testNo = 0;

    testResults.push_back(std::make_pair(testNo++, connectAndSenseVoltage()));

    for( ; testNo <= testconfig::TOTAL_TEST_NO; testNo++)
    {
        delay(40);
        servoController->pressButton();
        headerDurition = irManager->waitForHeaderBits();
        servoController->releaseButton();
        if((consecutiveErrorHeader + consecutiveErrorData) == 3){
            std::cout << "Test aborted...\n";
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
            break;
        }
        else if(headerDurition > testconfig::MIN_HEADER_DURATION && headerDurition < testconfig::MAX_HEADER_DURATION){
            for(int i=0; i<testconfig::IR_DATA_SIZE; i++)
                data[i] = irManager->readBit();

            if(irManager->checkPowerKey(data, testconfig::IR_DATA_SIZE)){
                consecutiveErrorHeader = 0;
                consecutiveErrorData = 0;
            }
            else{
                std::cout << "Data mismatch, test #" << testNo << std::endl;
                consecutiveErrorHeader = 0;
                consecutiveErrorData++;
                totalErrorData++;
            }
        }
        else{
            std::cout << "Could not catch the header, test #" << testNo << std::endl;
            consecutiveErrorHeader++;
            totalErrorHeader++;
            delete irManager;
            delay(200);
            irManager = new IrManager(inaConfig::IR_PIN);
            delay(2000);
        }

        if(testNo % testconfig::TEST_QUANTITY_TO_MEASURE == 0){
            std::cout << "Test #" << testNo << ", ";
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
        }

        if(testResults.size() == testconfig::MEASUREMENT_QUANTITY_TO_SAVE)
            saveRecordedMesuremants(testResults);

    }
    std::cout << "Total Test: " << testNo << ", Total error: " << totalErrorHeader + totalErrorData
                        << " (" << totalErrorHeader << " header, " << totalErrorData << " data)" << std::endl;
    if(testResults.size())
        saveRecordedMesuremants(testResults);
}

SolarlessIrButtonClick::~SolarlessIrButtonClick(){
    delete sensor;
    delete irManager;
    delete servoController;
    system("python3 ./graphTestResult.py --sibc");
}

SolarlessIrButtonClick::SolarlessIrButtonClick(){
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

float SolarlessIrButtonClick::connectAndSenseVoltage(){
    digitalWrite(inaConfig::RELAY_PIN, LOW);
    delay(50);
    float temp = sensor->voltage();
    digitalWrite(inaConfig::RELAY_PIN, HIGH);
    delay(50);
    return temp;
}

void SolarlessIrButtonClick::saveRecordedMesuremants(std::vector<std::pair<int, float>> &testResults){
        std::ofstream file("testResults.txt", std::ios::app);
        for (auto &result : testResults)
            file << "test" << result.first << ": " << result.second << std::endl;
        file.close();
        testResults.clear();
}
