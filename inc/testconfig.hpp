/**
  ******************************************************************************
  * @file    testconfig.hpp
  * @authors Cihan Senyuz
  * @date    28.04.2025
  * @brief   Header for configrable variables of test modules
  *                 This class contains variables for test module parameters.
  *          User must define the values of these variables according to the test
  *          requirements.
  *                 
  * 
  ******************************************************************************
  */

#pragma once

class TestSettings {
private:
    TestSettings() = default;
    TestSettings(const TestSettings&) = delete;
    TestSettings& operator=(const TestSettings&) = delete;

public:
    static TestSettings& getInstance() {
        static TestSettings instance;
        return instance;
    }

    // General
    const char* testResultsFileName = "testResults.txt";

    // IR
    struct IR {
        int dataSize = 24;
        int minHeaderDuration = 7800;
        int maxHeaderDuration = 8200;
    };

    // IR Signal Validation Test
    /*
      1- Her buton basımında IR sinyalinin header (başlık) kısmını ve IR verisini kontrol eder.
      2- Eğer arka arkaya TOTAL_ERROR_TO_FAIL_TEST kez yanlış okuma yapılırsa, testi sonlandırır.
      3- TEST_QUANTITY_TO_MEASURE testte bir, voltaj ölçümü yapar ve sonucu kaydeder.
      4- Her MEASUREMENT_QUANTITY_TO_SAVE ölçümde bir, hafızadaki test sonuçlarını 
        TEST_RESULTS_FILE_NAME dosyasına kaydeder.
      5- Toplamda TOTAL_TEST_NO test gerçekleştirilir. Bu değer TEST_QUANTITY_TO_MEASURE 
        ile tam bölünebilir olmalıdır.
    */
    struct IRSVT {
        int totalTestCount = 100000;
        int testQuantityToMeasure = 200;
        int measurementQuantityToSave = 20;
        int totalErrorToFailTest = 3;
    };

    // Battery Voltage and Button Test
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
    struct BVABT {
        int sleepSecondsWhenLowBattery = 900;
        int testTimeoutWhenLowBattery = 24;
        int sleepSecondsWhenHighBattery = 900;
    };

    // Battery Charge Monitoring Test
    /*
      1- Her SLEEP_SECONDS ara ile batarya voltajını ölçer.
      2- Eğer batarya voltajı BATT_LOW_THRESHOULD değerinin altına düşerse, test sonlanır.
    */
    struct BCMT {
      
        int sleepSeconds = 3600;
        float batteryLowThreshold = 2.66f;
    };
};