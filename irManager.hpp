/**
  ******************************************************************************
  * @file    irManager.hpp
  * @authors Cihan Senyuz, Hamdi Demircan Necli
  * @date    20.04.2024
  * @brief   Header for irManager.cpp file.
  *                 This file contains the common defines of the IrManager class.
  *          The IrManager class is used to manage the IR receiver module.
  *          This header depends on the wiringPi library.
  * 
  ******************************************************************************
  */

#ifndef IRMANAGER_HPP
#define IRMANAGER_HPP

#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std::chrono;

#define BIT0 0
#define BIT1 1
#define MAX_REMOTE_LATE_RESPONSE 350000 // in usec

class IrManager
{
public:
    IrManager(int irPin);
    ~IrManager();
    void waitForEdge();
    int waitForHeaderBits();
    bool readBit();
    bool checkPowerKey(bool* data, int size);
    static bool edgeFlag;
private:
    bool firstBitflag;
    int bitCounter;
    int irPin;
    bool powerKey[24] = { 0, 0, 0, 0, 0, 0, 0, 0,
                          1, 1, 0, 0, 1, 1, 1, 1,
                          0, 0, 0, 0, 1, 1, 0, 1 };
};

void gpoiIntHandler();

#endif // IRMANAGER_HPP