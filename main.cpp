#include "main.hpp"

Ina238 *sensor;
IrManager *irManager;
ServoController *servoController;

int main (int argc, char **argv)
{
    int data[24];
    int headerDurition = 0;
    short errorCounter = 0;
    short errorTotal = 0;
    setupTest();
    connectAndSenseVoltage();

    for(int testNo=1; testNo <= TOTAL_TEST_NO; testNo++)
    {
        std::cout << "\n--- #" << testNo << " test----\n";
        delay(1000);
        servoController->pressButton();
        //sensor->current();
        servoController->releaseButton();
        headerDurition = irManager->waitForHeaderBits();

        if(headerDurition > 7800 && headerDurition < 8200){
            for(int i=0; i<24; i++){
                data[i] = irManager->readBit();
                //if(data[i] == -1)
                //   std::cerr << " bit no: " << i << std::endl;
            }
            if(irManager->checkPowerKey(data)){
                std::cout << "Data correct: ";
                errorCounter = 0;
            }
            else{
                std::cout << "!!! Data NOT correct: ";
                errorCounter++;
                errorTotal++;
            }
            for(auto bit : data)
                std::cout << bit << " ";
            std::cout << std::endl;
        }
        else if(errorCounter == 3){
            std::cout << "test terminated...\n";
            break;
        }
        else{
            std::cout << "could not catch the header\n";
            errorCounter++;
            errorTotal++;
        }
    }
    connectAndSenseVoltage();
    std::cout << "Total Test: " << TOTAL_TEST_NO << ", Total error: " << errorTotal << std::endl;
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

void connectAndSenseVoltage(){
    digitalWrite(RELAY_PIN, LOW);
    delay(50);
    sensor->voltage();
    digitalWrite(RELAY_PIN, HIGH);
}