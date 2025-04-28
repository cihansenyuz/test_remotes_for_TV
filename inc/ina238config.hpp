/**
  ******************************************************************************
  * @file    ina238config.hpp
  * @authors Cihan Senyuz
  * @date    16.04.2025
  * @brief   Header for configrable variables of ina238 module hardware.
  *                 This class contains modifiable variables for the INA238 module.
  *          These values should not be changed unless the hardware is changed.
  *                 
  * 
  ******************************************************************************
  */

#pragma once

#include <cstdint>

class INA238Config {
  public:
      static INA238Config& getInstance() {
          static INA238Config instance;
          return instance;
      }
  
      uint8_t getDeviceAddress() const { return deviceAddress; }
      uint8_t getBusNumber() const { return busNumber; }
      double getShuntResistance() const { return shuntResistance; }
      double getMaxCurrent() const { return maxCurrent; }
      int getIRPin() const { return irPin; }
      int getServoPin() const { return servoPin; }
      int getRelayPin() const { return relayPin; }
  
      void setDeviceAddress(uint8_t address) { deviceAddress = address; }
      void setBusNumber(uint8_t bus) { busNumber = bus; }
      void setShuntResistance(double resistance) { shuntResistance = resistance; }
      void setMaxCurrent(double current) { maxCurrent = current; }
      void setIRPin(int pin) { irPin = pin; }
      void setServoPin(int pin) { servoPin = pin; }
      void setRelayPin(int pin) { relayPin = pin; }
  
  private:
      INA238Config() = default;
  
      uint8_t deviceAddress = 0x40; // Default I2C address
      uint8_t busNumber = 1; // Default I2C bus number
      double shuntResistance = 0.022; // Default shunt resistance
      double maxCurrent = 0.05; // Default max current
      int irPin = 0; // Default GPIO pin for IR receiver
      int servoPin = 23; // Default GPIO pin for servo motor
      int relayPin = 25; // Default GPIO pin for relay
  };