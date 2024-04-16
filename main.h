#include "ina238.h"
#include <wiringPi.h>

#define DEVICE_ADDRESS 0x40
#define BUS_NUMBER 1
#define SHUNT_RESISTANCE 0.022
#define MAX_CURRENT 0.05

void setup();
void gpoiIntHandler();
