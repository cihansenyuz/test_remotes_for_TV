/**
  ******************************************************************************
  * @file    servoController.hpp
  * @authors Cihan Senyuz, Hamdi Demircan Necli
  * @date    20.05.2023
  * @brief   Header for servoController.cpp file.
  *                 This file contains the common defines of the ServoController class.
  *          The ServoController class is used to manage servo motor MG995, press a 
  *          button on the remote.
  *          This header depends on the wiringPi library.
  *                 
  * 
  ******************************************************************************
  */

#ifndef SERVOCONTROLLER_HPP
#define SERVOCONTROLLER_HPP

#include "wiringPi.h"

class ServoController
{
public:
    ServoController(int _servoPin);
    ~ServoController();
    void pressButton();
    void releaseButton();
    void setPosition(int pos);  // min 18, max 130
private:
    int servoPin;
};

#endif // SERVOCONTROLLER_HPP