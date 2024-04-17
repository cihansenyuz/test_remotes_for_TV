#include "main.hpp"

Ina238 *device;
IrManager *irManager;
ServoController *servoController;
bool data[24];
int headerDurition = 0;

int main (int argc, char **argv)
{
    setupModules();
    
    std::cout << "Test beginning\n";
    int count = 3;
    while(count--)
    {
        delay(1000);
        servoController->pressButton();
        // device->current();
        servoController->releaseButton();

        //auto first = std::chrono::high_resolution_clock::now();
        headerDurition = irManager->waitForHeaderBits();

        if(headerDurition > 7900 && headerDurition < 8100){
            for(int i=0; i<24; i++){
                data[i] = irManager->readBit();
            }
            for(auto bit : data)
                std::cout << bit << " ";
            std::cout << std::endl;
            if(irManager->checkPowerKey(data))
                std::cout << "Data correct\n";
            else
                std::cout << "Data not correct\n";
        }
        else
            std::cout << "Header durition is not correct\n";
        //auto second = std::chrono::high_resolution_clock::now();
        //std::cout << (std::chrono::duration_cast<std::chrono::microseconds>(second - first)).count() << " us\n";
        std::cout << "next run\n";
    }
    delete device;
    delete irManager;
    delete servoController;
    return 0;
}

void setupModules(){
    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;

    device = new Ina238(DEVICE_ADDRESS, BUS_NUMBER);
    device->setShuntCal(SHUNT_RESISTANCE, MAX_CURRENT);
    irManager = new IrManager(IR_PIN);
    servoController = new ServoController(SERVO_PIN);
}