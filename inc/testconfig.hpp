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

namespace testconfig{
  constexpr const char* TEST_RESULTS_FILE_NAME = "testResults.txt";

  namespace IR{
    constexpr int IR_DATA_SIZE = 24; /** toplam IR datası boyutu */
    constexpr int MIN_HEADER_DURATION = 7800;
    constexpr int MAX_HEADER_DURATION = 8200;
  }

  namespace IRSVT{ // IrSignalValidationTest
    /*
    1- Her buton basımında IR sinyalinin header (başlık) kısmını ve IR verisini kontrol eder.
    2- Eğer arka arkaya TOTAL_ERROR_TO_FAIL_TEST kez yanlış okuma yapılırsa, testi sonlandırır.
    3- TEST_QUANTITY_TO_MEASURE testte bir, voltaj ölçümü yapar ve sonucu kaydeder.
    4- Her MEASUREMENT_QUANTITY_TO_SAVE ölçümde bir, hafızadaki test sonuçlarını 
       TEST_RESULTS_FILE_NAME dosyasına kaydeder.
    5- Toplamda TOTAL_TEST_NO test gerçekleştirilir. Bu değer TEST_QUANTITY_TO_MEASURE 
       ile tam bölünebilir olmalıdır.
    */
    constexpr int TOTAL_TEST_NO = 100000; // must be integer multiple of TEST_QUANTITY_TO_MEASURE
    constexpr int TEST_QUANTITY_TO_MEASURE = 200;
    constexpr int MEASUREMENT_QUANTITY_TO_SAVE = 20;
    constexpr int TOTAL_ERROR_TO_FAIL_TEST = 3;
  }

  namespace BVABT{ // BatteryVoltageAndButtonTest
    /*
      1- Batarya yeterli seviyedeyken, her 50 buton basımında bir 
         SLEEP_SECONDS_WHEN_HIGH_BATT kadar süre bekler.
      2- Batarya düşük seviyedeyken, SLEEP_SECONDS_WHEN_LOW_BATT kadar
         süre bekleyerek bataryayı kontrol eder.
      3- Eğer batarya düşük seviyedeyken TEST_TIMEOUT_WHEN_LOW_BATT 
         çarpı SLEEP_SECONDS_WHEN_LOW_BATT kadar süre boyunca IR sinyali 
         okuma yapılamazsa, testi sonlandırır. Eğer okuma yapılabilirse, 
         tekrar 1. adıma döner.
    */
    constexpr int SLEEP_SECONDS_WHEN_LOW_BATT = 900; // in seconds
    constexpr int TEST_TIMEOUT_WHEN_LOW_BATT = 24; // times SLEEP_SECONDS_WHEN_LOW_BATT
    constexpr int SLEEP_SECONDS_WHEN_HIGH_BATT = 900; // in seconds
  }

  namespace BCMT{ // BatteryChargeMonitoringTest
    /*
    1- Her SLEEP_SECONDS ara ile batarya voltajını ölçer.
    2- Eğer batarya voltajı BATT_LOW_THRESHOULD değerinin altına düşerse, test sonlanır.
    */
    constexpr int SLEEP_SECONDS = 3600;
    constexpr float BATT_LOW_THRESHOULD = 2.66f;
  }
}