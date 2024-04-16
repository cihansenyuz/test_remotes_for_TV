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