#pragma once

#include <cstdint>

namespace inaConfig{
    constexpr uint8_t DEVICE_ADDRESS = 0x40; // I2C address of the INA238
    constexpr uint8_t BUS_NUMBER = 1; // I2C bus number

    constexpr double SHUNT_RESISTANCE = 0.022; // Shunt resistance in ohms
    constexpr double MAX_CURRENT = 0.05; // Maximum current in amperes

    constexpr int IR_PIN = 0; // GPIO pin number(wiringPi) for IR receiver
    constexpr int SERVO_PIN = 23; // GPIO pin number(wiringPi) for servo motor
    constexpr int RELAY_PIN = 25; // GPIO pin number(wiringPi) for relay
}