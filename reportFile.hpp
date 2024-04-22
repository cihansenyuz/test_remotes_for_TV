/**
  ******************************************************************************
  * @file    reportFile.hpp
  * @authors Cihan Senyuz, Hamdi Demircan Necli
  * @date    20.04.2024
  * @brief   Header for reportFile.cpp file.
  *                 This file contains the common defines of the ReportFile class.
  *          The ReportFile class is used to manage the voltage measurements.
  *          This header depends on the fstream library.
  * 
  ******************************************************************************
  */

#ifndef REPORTFILE_HPP
#define REPORTFILE_HPP

#include <iostream>
#include <fstream>
#include <vector>

class ReportFile{
public:
    ReportFile() {}
    ~ReportFile() {}
    void measureAndSave(double voltage_value) {};
private:
    std::vector<double> voltages; 
    void save(double voltage_value) {};
};

#endif // REPORTFILE_HPP