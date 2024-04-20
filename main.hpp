#include "ina238.hpp"
#include "irManager.hpp"
#include "servoController.hpp"
#include <wiringPi.h>
#include <stdio.h>

#define DEVICE_ADDRESS 0x40
#define BUS_NUMBER 1
#define SHUNT_RESISTANCE 0.022
#define MAX_CURRENT 0.05

#define IR_PIN 0        // wiringPi pin number
#define SERVO_PIN 23    // wiringPi pin number
#define RELAY_PIN 25    // wiringPi pin number

#define TOTAL_TEST_NO 10
#define TOTAL_VOLTAGE_MEASUREMENTS 1   // TOTAL_TEST_NO / 200 + 1 // min 1
#define IR_DATA_SIZE 24
#define MIN_HEADER_DURATION 7800
#define MAX_HEADER_DURATION 8200

void setupTest();
float connectAndSenseVoltage();
