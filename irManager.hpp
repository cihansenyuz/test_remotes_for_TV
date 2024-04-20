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
    void waitForEdge();
    int waitForHeaderBits();
    int readBit();
    bool checkPowerKey(int* data, int size);
    //static bool edgeFlag;
private:
    bool firstBitflag;
    int bitCounter;
    int irPin;
    int powerKey[24] = { 0, 0, 0, 0, 0, 0, 0, 0,
                          1, 1, 0, 0, 1, 1, 1, 1,
                          0, 0, 0, 0, 1, 1, 0, 1 };
};

//void gpoiIntHandler();