#include "main.h"

Ina238 *device;
const int irPin = 0;
bool flag = true;

int main (int argc, char **argv)
{
    setup();
    
    std::cout << digitalRead(irPin) << std::endl;
    wiringPiISR(irPin, INT_EDGE_FALLING, &gpoiIntHandler);

    while(flag)
    {}

    device->current();

    delete device;
    return 0;
}

void gpoiIntHandler(){
    flag = false;
}

void setup(){
    device = new Ina238(DEVICE_ADDRESS, BUS_NUMBER);
    device->setShuntCal(SHUNT_RESISTANCE, MAX_CURRENT);

    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;
    pinMode(irPin, INPUT);
    pullUpDnControl(irPin, PUD_DOWN);
}