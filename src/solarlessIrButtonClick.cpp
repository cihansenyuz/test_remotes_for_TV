#include "solarlessIrButtonClick.hpp"

Ina238 *sensor;
IrManager *irManager;
ServoController *servoController;


int main (int argc, char **argv)
{
    bool data[IR_DATA_SIZE];
    std::vector<std::pair<int, float>> testResults;
    int headerDurition = 0;
    short totalErrorHeader = 0;
    short totalErrorData = 0;
    short consecutiveErrorHeader = 0;
    short consecutiveErrorData = 0;
    int testNo = 0;

    setupTest();
    testResults.push_back(std::make_pair(testNo++, connectAndSenseVoltage()));

    for( ; testNo <= TOTAL_TEST_NO; testNo++)
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
        else if(headerDurition > MIN_HEADER_DURATION && headerDurition < MAX_HEADER_DURATION){
            for(int i=0; i<IR_DATA_SIZE; i++)
                data[i] = irManager->readBit();

            if(irManager->checkPowerKey(data, IR_DATA_SIZE)){
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
            irManager = new IrManager(IR_PIN);
            delay(2000);
        }

        if(testNo % TEST_QUANTITY_TO_MEASURE == 0){
            std::cout << "Test #" << testNo << ", ";
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
        }

        if(testResults.size() == MEASUREMENT_QUANTITY_TO_SAVE)
            saveRecordedMesuremants(testResults);

    }
    std::cout << "Total Test: " << testNo << ", Total error: " << totalErrorHeader + totalErrorData
                        << " (" << totalErrorHeader << " header, " << totalErrorData << " data)" << std::endl;
    if(testResults.size())
        saveRecordedMesuremants(testResults);

    delete sensor;
    delete irManager;
    delete servoController;
    //system("python3 ./graphTestResult.py");
    return 0;
}

void setupTest(){
    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;

    sensor = new Ina238(DEVICE_ADDRESS, BUS_NUMBER);
    sensor->setShuntCal(SHUNT_RESISTANCE, MAX_CURRENT);
    irManager = new IrManager(IR_PIN);
    servoController = new ServoController(SERVO_PIN);
    
    // Relay setup
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
}

float connectAndSenseVoltage(){
    digitalWrite(RELAY_PIN, LOW);
    delay(50);
    float temp = sensor->voltage();
    digitalWrite(RELAY_PIN, HIGH);
    delay(50);
    return temp;
}

void saveRecordedMesuremants(std::vector<std::pair<int, float>> &testResults){
        std::ofstream file("testResults.txt", std::ios::app);
        for (auto &result : testResults)
            file << "test" << result.first << ": " << result.second << std::endl;
        file.close();
        testResults.clear();
}
