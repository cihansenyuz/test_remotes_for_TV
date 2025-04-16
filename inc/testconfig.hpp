/**
  ******************************************************************************
  * @file    testconfig.hpp
  * @authors Cihan Senyuz
  * @date    16.04.2025
  * @brief   Header for configrable variables of test modules
  *                 This file contains constant variables for test modules.
  *          User must define the values of these variables according to the test
  *          requirements.
  *                 
  * 
  ******************************************************************************
  */

#pragma once

namespace testconfig
{
    constexpr int TOTAL_TEST_NO = 100000; // integer multiple of TEST_QUANTITY_TO_MEASURE
    constexpr int TEST_QUANTITY_TO_MEASURE = 200;
    constexpr int MEASUREMENT_QUANTITY_TO_SAVE = 20;
    constexpr int IR_DATA_SIZE = 24;
    constexpr int MIN_HEADER_DURATION = 7800;
    constexpr int MAX_HEADER_DURATION = 8200;
}