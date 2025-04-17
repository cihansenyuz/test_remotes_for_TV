/**
  ******************************************************************************
  * @file    remotetest.hpp
  * @authors Cihan Senyuz
  * @date    17.04.2025
  * @brief   Header for abstract base class of other test classes.
  *                 runTest behaviour must be overriden in derived classes
  *                 protected behaviours are virtual to have option to be
  *          overridden if necessary in derived classes.
  * 
  ******************************************************************************
  */

#pragma once

class RemoteTest {
public:
    virtual ~RemoteTest() = default;
    virtual void runTest() = 0;

protected:
    virtual float connectAndSenseVoltage();
    virtual void saveRecordedMesuremants(struct tm* localTime, float &voltage);
};