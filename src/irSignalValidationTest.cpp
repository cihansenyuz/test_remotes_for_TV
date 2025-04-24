#include "irSignalValidationTest.hpp"
#include "ina238config.hpp"
#include "testconfig.hpp"

#include <fstream>
#include <wiringPi.h>
#include <stdio.h>

void IrSignalValidationTest::runTest()
{
    bool data[testconfig::IR::IR_DATA_SIZE];
    testResults.reserve(testconfig::IRSVT::TOTAL_TEST_NO);
    testResults.push_back(std::make_pair(testNo++, connectAndSenseVoltage()));

    for( ; testNo <= testconfig::IRSVT::TOTAL_TEST_NO; testNo++)
    {
        delay(40);
        servoController->pressButton();
        headerDurition = irManager->waitForHeaderBits();
        servoController->releaseButton();
        if((consecutiveErrorHeader + consecutiveErrorData)
            == testconfig::IRSVT::TOTAL_ERROR_TO_FAIL_TEST){
            std::cout << "Test aborted...\n";
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
            break;
        }
        else if(headerDurition > testconfig::IR::MIN_HEADER_DURATION
                && headerDurition < testconfig::IR::MAX_HEADER_DURATION){
            for(int i=0; i<testconfig::IR::IR_DATA_SIZE; i++)
                data[i] = irManager->readBit();

            if(irManager->checkPowerKey(data, testconfig::IR::IR_DATA_SIZE)){
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

        if(testNo % testconfig::IRSVT::TEST_QUANTITY_TO_MEASURE == 0){
            std::cout << "Test #" << testNo << ", ";
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
        }

        if(testResults.size() == testconfig::IRSVT::MEASUREMENT_QUANTITY_TO_SAVE)
            saveRecordedMesuremants();

    }
    std::cout << "Total Test: " << testNo << ", Total error: " << totalErrorHeader + totalErrorData
                        << " (" << totalErrorHeader << " header, " << totalErrorData << " data)" << std::endl;
    if(testResults.size())
        saveRecordedMesuremants();
}

IrSignalValidationTest::~IrSignalValidationTest(){
    delete sensor;
    delete irManager;
    delete servoController;
    system("python3 ./graphTestResult.py --sibc");
    emit finished();
}

IrSignalValidationTest::IrSignalValidationTest(){
    irManager = new IrManager(inaConfig::IR_PIN);
    servoController = new ServoController(inaConfig::SERVO_PIN);
}

void IrSignalValidationTest::saveRecordedMesuremants(){
        std::ofstream file(testconfig::TEST_RESULTS_FILE_NAME, std::ios::app);
        for (auto &result : testResults)
            file << "test" << result.first << ": " << result.second << std::endl;
        file.close();
        testResults.clear();
}
