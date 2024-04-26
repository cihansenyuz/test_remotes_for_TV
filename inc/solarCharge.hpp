#include "ina238.hpp"
#include <wiringPi.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <unistd.h>

#define DEVICE_ADDRESS 0x40
#define BUS_NUMBER 1
#define RELAY_PIN 25    // wiringPi pin number
#define TEST_DURATION 

using namespace std::chrono;

void setupTest();
float connectAndSenseVoltage();
void saveRecordedMesuremants(struct tm* localTime, float &voltage);