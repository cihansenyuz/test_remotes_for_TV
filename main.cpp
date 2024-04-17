#include "main.hpp"

Ina238 *sensor;
IrManager *irManager;
ServoController *servoController;

int main (int argc, char **argv)
{
    int data[24];
    int headerDurition = 0;
    setupModules();

    for(int testNo=1; testNo <= TOTAL_TEST_NO; testNo++)
    {
        std::cout << "\n--- #" << testNo << " test----\n";
        delay(1000);
        servoController->pressButton();
        // sensor->current();
        servoController->releaseButton();
        headerDurition = irManager->waitForHeaderBits();

        if(headerDurition > 7900 && headerDurition < 8100){
            for(int i=0; i<24; i++){
                data[i] = irManager->readBit();
                //if(data[i] == -1)
                //   std::cerr << " bit no: " << i << std::endl;
            }
            if(irManager->checkPowerKey(data))
                std::cout << "Data correct: ";
            else
                std::cout << "!!! Data NOT correct: ";
            for(auto bit : data)
                std::cout << bit << " ";
            std::cout << std::endl;
        }
        else
            std::cout << "could not catch the header\n";
    }

    delete sensor;
    delete irManager;
    delete servoController;
    return 0;
}

void setupModules(){
    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;

    sensor = new Ina238(DEVICE_ADDRESS, BUS_NUMBER);
    sensor->setShuntCal(SHUNT_RESISTANCE, MAX_CURRENT);
    irManager = new IrManager(IR_PIN);
    servoController = new ServoController(SERVO_PIN);
}