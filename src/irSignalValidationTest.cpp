#include "irSignalValidationTest.hpp"
#include "ina238config.hpp"
#include "testconfig.hpp"

#include <fstream>
#include <wiringPi.h>
#include <stdio.h>

void IrSignalValidationTest::runTest()
{
    bool data[TestSettings::IR::dataSize];
    testResults.reserve(TestSettings::IRSVT::totalTestCount);
    testResults.push_back(std::make_pair(testNo++, connectAndSenseVoltage()));

    for( ; testNo <= TestSettings::IRSVT::totalTestCount; testNo++)
    {
        delay(40);
        servoController->pressButton();
        headerDurition = irManager->waitForHeaderBits();
        servoController->releaseButton();
        if((consecutiveErrorHeader + consecutiveErrorData)
            == TestSettings::IRSVT::totalErrorToFailTest){
            std::cout << "Test aborted...\n";
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
            break;
        }
        else if(headerDurition > TestSettings::IR::maxHeaderDuration
                && headerDurition < TestSettings::IR::maxHeaderDuration){
            for(int i=0; i<TestSettings::IR::dataSize; i++)
                data[i] = irManager->readBit();

            if(irManager->checkPowerKey(data, TestSettings::IR::dataSize)){
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
            irManager = new IrManager(INA238Config::getInstance().getIRPin());
            delay(2000);
        }

        if(testNo % TestSettings::IRSVT::testQuantityToMeasure == 0){
            std::cout << "Test #" << testNo << ", ";
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
        }

        if(testResults.size() == TestSettings::IRSVT::measurementQuantityToSave)
            saveRecordedMesuremants();

    }
    std::cout << "Total Test: " << testNo << ", Total error: " << totalErrorHeader + totalErrorData
                        << " (" << totalErrorHeader << " header, " << totalErrorData << " data)" << std::endl;
    if(testResults.size())
        saveRecordedMesuremants();
    
    std::cout << "[IrSignalValidationTest][runTest] test finished, emit signal" << std::endl;
    emit finished();
}

IrSignalValidationTest::~IrSignalValidationTest(){
    delete irManager;
    delete servoController;
    //system("python3 ./graphTestResult.py --sibc");
}

IrSignalValidationTest::IrSignalValidationTest(){
    irManager = new IrManager(INA238Config::getInstance().getIRPin());
    servoController = new ServoController(INA238Config::getInstance().getServoPin());
}

void IrSignalValidationTest::saveRecordedMesuremants(){
        std::ofstream file(TestSettings::testResultsFileName, std::ios::app);
        for (auto &result : testResults)
            file << "test" << result.first << ": " << result.second << std::endl;
        file.close();
        testResults.clear();
}
