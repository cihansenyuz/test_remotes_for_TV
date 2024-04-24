#include "main.hpp"

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

    setupTest();
    testResults.push_back(std::make_pair(0, connectAndSenseVoltage()));

    for(int testNo=1; testNo <= TOTAL_TEST_NO; testNo++)
    {
        servoController->pressButton();
        servoController->releaseButton();

        headerDurition = irManager->waitForHeaderBits();
        
        if((consecutiveErrorHeader + consecutiveErrorData) == 3){
            std::cout << "Test terminated... Total test: " << testNo-1 << ", Total error: " << totalErrorHeader + totalErrorData
                                                                       << " (" << totalErrorHeader << " header, "
                                                                       << " " << totalErrorData << " data)" << std::endl;
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
            saveRecordedMesuremants(testResults);
            break;
        }
        else if(headerDurition > MIN_HEADER_DURATION && headerDurition < MAX_HEADER_DURATION){
            for(int i=0; i<IR_DATA_SIZE; i++){
                data[i] = irManager->readBit();
            }
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
        }

        if(testNo % 200 == 0){
            std::cout << "Test #" << testNo << ", ";
            testResults.push_back(std::make_pair(testNo, connectAndSenseVoltage()));
        }

        if(testResults.size() == 100)
            saveRecordedMesuremants(testResults);

    }
    if((consecutiveErrorHeader + consecutiveErrorData) < 3)
        std::cout << "Total Test: " << TOTAL_TEST_NO << ", Total error: " << totalErrorHeader + totalErrorData
                                                                     << " (" << totalErrorHeader << " header, "
                                                                     << " " << totalErrorData << " data)" << std::endl;
    system("python3 ./graphTestResult.py");

    delete sensor;
    delete irManager;
    delete servoController;
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