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

  namespace solarlessIrButtonClick{
    /*
    1- her basımda header ve IR datasını kontrol eder
    2- peşpeşe TOTAL_ERROR_TO_FAIL_TEST kez yanlış okursa
    testi sonlandırır.
    3- her MEASUREMENT_QUANTITY_TO_SAVE okumada bir hafızadaki ölçümleri
    TEST_RESULTS_FILE_NAME dosyasına yazar.
    */
    constexpr int TOTAL_TEST_NO = 100000; // must be integer multiple of TEST_QUANTITY_TO_MEASURE
    constexpr int TEST_QUANTITY_TO_MEASURE = 200;
    constexpr int MEASUREMENT_QUANTITY_TO_SAVE = 20;
    constexpr int TOTAL_ERROR_TO_FAIL_TEST = 3;
  }

  namespace pushandmeas{
    /*
      1- Batarya bitene kadar 50 kez SLEEP_SECONDS_WHEN_HIGH_BATT
      sn ara ile basım yapar.
      2- Batarya bitince SLEEP_SECONDS_WHEN_LOW_BATT sn ara ile
      basım deneyerek bataryayı kontrol eder.
      3- TEST_TIMEOUT_WHEN_LOW_BATT kez basıma karşılık IR okuma
      yapamazsa, testi sonlandırır. Okuma yaparsa tekrar 1. adıma
      döner. 
    */
    constexpr int SLEEP_SECONDS_WHEN_LOW_BATT = 900; // in seconds
    constexpr int TEST_TIMEOUT_WHEN_LOW_BATT = 24; // times SLEEP_SECONDS_WHEN_LOW_BATT
    constexpr int SLEEP_SECONDS_WHEN_HIGH_BATT = 900; // in seconds
  }

  namespace solarcharge{
    /*
    1- SLEEP_SECONDS ara ile batarya voltajı ölçer
    2- batarya BATT_LOW_THRESHOULD 'ın altına düşerse, test sonlanır
    */
    constexpr int SLEEP_SECONDS = 3600;
    constexpr float BATT_LOW_THRESHOULD = 2.66f;
  }
}