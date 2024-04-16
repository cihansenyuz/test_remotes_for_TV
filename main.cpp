#include "main.hpp"

Ina238 *device;
IrManager *irManager;
ServoController *servoController;
bool data[24];

int main (int argc, char **argv)
{
    setupModules();
    while(1){
        servoController->pushButton();
        int headerDurition = irManager->waitForHeaderBits();
        
        if(headerDurition > 7900 && headerDurition < 8100){
            for(int i=0; i<24; i++){
                data[i] = irManager->readBit();
            }
        }
        servoController->releaseButton();
        for(auto bit : data)
        std::cout << bit << " ";
        delay(2000);
    }
    
    delete device;
    delete irManager;
    delete servoController;
    return 0;
}

void setupModules(){
    device = new Ina238(DEVICE_ADDRESS, BUS_NUMBER);
    device->setShuntCal(SHUNT_RESISTANCE, MAX_CURRENT);
    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;
    irManager = new IrManager(IR_PIN);
    servoController = new ServoController(SERVO_PIN);
}