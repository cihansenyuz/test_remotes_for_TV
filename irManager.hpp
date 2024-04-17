#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

class IrManager
{
public:
    IrManager(int irPin);
    ~IrManager();
    int waitForHeaderBits();
    int readBit();
    void waitForEdge();
    bool checkPowerKey(int* data);
    static bool edgeFlag;
private:
    /*std::chrono::_V2::system_clock::time_point headerStartTime;
    std::chrono::_V2::system_clock::time_point headerEndTime;
    std::chrono::_V2::system_clock::time_point dataStartTime;
    std::chrono::_V2::system_clock::time_point dataEndTime;*/
    bool firstBitflag;
    int bitCounter;
    int irPin;
    int powerKey[24] = { 0, 0, 0, 0, 0, 0, 0, 0,
                          1, 1, 0, 0, 1, 1, 1, 1,
                          0, 0, 0, 0, 1, 1, 0, 1 };
};

void gpoiIntHandler();