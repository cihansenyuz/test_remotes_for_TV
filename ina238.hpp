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

class Ina238 {
public:
    Ina238(uint8_t addr, int busNum);
    ~Ina238(){}
    uint16_t getWordData(uint8_t reg);
    void writeWordData(int fd, uint8_t reg, uint16_t data);
    void setShuntCal(double res, double maxCur);
    uint16_t reverseWord(uint16_t oldWord);
    bool checkDevice();
    void deviceID();
    void temperature();
    float voltage();
    float current();
private:
    int fd;
    int m_bus;
    uint8_t m_addr;
    double m_currentLsb;
};

#endif // INA238_HPP