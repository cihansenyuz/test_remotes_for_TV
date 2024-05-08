/**
  ******************************************************************************
  * @file    ina238.hpp
  * @authors Cihan Senyuz
  * @date    20.04.2024
  * @brief   Header for ina238.cpp file.
  *                 This file contains the common defines of the Ina238 class.
  *          The Ina238 class is used to manage INA238 Power Monitor, read the
  *          current and voltage values. SetShuntCal function may need to be
  *          fine tuned.
  *          This header depends on the wiringPi library.
  *                 
  * 
  ******************************************************************************
  */

#ifndef INA238_HPP
#define INA238_HPP

#include <iostream>
#include <cmath>
#include <wiringPiI2C.h>
#include <chrono>
#include <thread>

#define DEVICE_ID 0x3F        // slave device ID register
#define CONFIG 0x00           // Configuration (CONFIG) Register
#define ADC_CONFIG 0x01       // ADC Configuration (ADC_CONFIG) Register
#define SHUNT_CAL 0x02        // Shunt calibration
#define VSHUNT 0x04           // Shunt Voltage Measurement
#define VBUS 0x05             // Bus Voltage Measurement
#define DIETEMP 0x06          // Temperature Measurement (DIETEMP) Register
#define CURRENT 0x07          // Current result
#define POWER 0x08            // Power result
#define DIAG_ALRT  0x0B       // Alerts

#define CONVERSION_VBUS_SHIFT 9
#define CONVERSION_VSHUNT_SHIFT 6
#define CONVERSION_TEMP_SHIFT 3
#define ADC_CONVERSION_MASK 0x07

typedef enum Sensor_t{
    vbusSense = 0,
    vshuntSense = 1,
    tempratureSense = 2
}Sensor_t;

typedef enum ConversionTime_t{
    t50us = 0,
    t84us = 1,
    t150us = 2,
    t280us = 3,
    t540us = 4,
    t1052us = 5,
    t2074us = 6,
    t4120us = 7
}ConversionTime_t;

class Ina238 {
public:
    Ina238(uint8_t addr, int busNum);
    ~Ina238(){}
    void setShuntCal(double res, double maxCur);  // max current in mA
    uint16_t reverseWord(uint16_t oldWord);
    bool checkDevice();
    void deviceID();
    void temperature();
    float voltage();
    float current();
    uint16_t getAlerts();
private:
    int fd;
    int m_bus;
    float m_maxCurrent;
    uint8_t m_addr;
    double m_currentLsb;

    uint16_t getWordData(uint8_t reg);
    void writeWordData(int fd, uint8_t reg, uint16_t data);
    void waitForConversion(Sensor_t sensor);
};

#endif // INA238_HPP