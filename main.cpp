#include "main.hpp"

Ina238 *sensor;
IrManager *irManager;
ServoController *servoController;


int main (int argc, char **argv)
{
    bool data[IR_DATA_SIZE];
    std::vector<float> voltages;
    int headerDurition = 0;
    short totalErrorHeader = 0;
    short totalErrorData = 0;
    short consecutiveErrorHeader = 0;
    short consecutiveErrorData = 0;

    setupTest();
    voltages.push_back(connectAndSenseVoltage());

    for(int testNo=1; testNo <= TOTAL_TEST_NO; testNo++)
    {
        std::cout << "--- #" << testNo << " test----\n";
        delay(500);
        servoController->pressButton();
        servoController->releaseButton();
        headerDurition = irManager->waitForHeaderBits();

        if(headerDurition > MIN_HEADER_DURATION && headerDurition < MAX_HEADER_DURATION){
            for(int i=0; i<IR_DATA_SIZE; i++){
                data[i] = irManager->readBit();
            }
            if(irManager->checkPowerKey(data, IR_DATA_SIZE)){
                consecutiveErrorHeader = 0;
                consecutiveErrorData = 0;
            }
            else{
                std::cout << "Data mismatch\n";
                consecutiveErrorHeader = 0;
                consecutiveErrorData++;
                totalErrorData++;
            }
        }
        else if((consecutiveErrorHeader + consecutiveErrorData) == 3){
            std::cout << "Test terminated... Total test: " << testNo-1 << ", Total error: " << totalErrorHeader + totalErrorData
                                                                       << " (" << totalErrorHeader << " header, "
                                                                       << " " << totalErrorData << " data)" << std::endl;
            voltages.push_back(connectAndSenseVoltage());
            saveRecordedMesuremants(voltages);
            break;
        }
        else{
            std::cout << "Could not catch the header\n";
            consecutiveErrorHeader++;
            totalErrorHeader++;
        }
        
        if(testNo % 200 == 0)
            voltages.push_back(connectAndSenseVoltage());
        
        if(voltages.size() % 100 == 0)
            saveRecordedMesuremants(voltages);

    }
    if((consecutiveErrorHeader + consecutiveErrorData) < 3)
        std::cout << "Total Test: " << TOTAL_TEST_NO << ", Total error: " << totalErrorHeader + totalErrorData
                                                                     << " (" << totalErrorHeader << " header, "
                                                                     << " " << totalErrorData << " data)" << std::endl;

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
    return temp;
}

void saveRecordedMesuremants(std::vector<float> &voltages) {
        std::ofstream file("voltage_measurements.txt", std::ios::app);
        for (int i = 0; i < voltages.size(); i++) {
            file << voltages[i] << std::endl;
        }
        file.close();
        voltages.clear();
}