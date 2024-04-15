#include "ina238.h"

#define DEVICE_ADDRESS 0x40
#define BUS_NUMBER 1
#define SHUNT_RESISTANCE 0.022
#define MAX_CURRENT 0.05

int main (int argc, char **argv){

    Ina238 device(DEVICE_ADDRESS, BUS_NUMBER);
    device.setShuntCal(SHUNT_RESISTANCE, MAX_CURRENT);
    
    /*float sum = 0;
    for(int i=0; i<128; i++)
        sum += device.current();

    std::cout << "average: " << sum/128 << std::endl;*/

    device.current();
    device.current();
    device.current();
    return 0;
}