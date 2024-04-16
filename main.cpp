#include "main.hpp"

Ina238 *device;
IrManager *irManager;
bool data[24];

int main (int argc, char **argv)
{
    setupModules();
    
    int headerDurition = irManager->waitForHeaderBits();
    if(headerDurition > 7900 && headerDurition < 8100){
        for(int i=0; i<24; i++){
            data[i] = irManager->readBit();
        }
    }

    for(auto bit : data)
        std::cout << bit << " ";

    delete device;
    delete irManager;
    return 0;
}

void setupModules(){
    device = new Ina238(DEVICE_ADDRESS, BUS_NUMBER);
    device->setShuntCal(SHUNT_RESISTANCE, MAX_CURRENT);

    irManager = new IrManager(IR_PIN);
}