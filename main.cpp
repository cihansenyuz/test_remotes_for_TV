#include "ina238.h"
#include <wiringPi.h>

#define DEVICE_ADDRESS 0x40
#define BUS_NUMBER 1
#define SHUNT_RESISTANCE 0.022
#define MAX_CURRENT 0.05

const int irPin = 0;
bool flag = true;

void gpoiIntHandler(){
    flag = false;
}

int main (int argc, char **argv){

    Ina238 device(DEVICE_ADDRESS, BUS_NUMBER);
    device.setShuntCal(SHUNT_RESISTANCE, MAX_CURRENT);
    
    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;

    pinMode(irPin, INPUT);
    pullUpDnControl(irPin, PUD_DOWN);

    std::cout << digitalRead(irPin);

    wiringPiISR(irPin, INT_EDGE_FALLING, &gpoiIntHandler);

    while(flag)
    {}

    device.current();
    return 0;
}