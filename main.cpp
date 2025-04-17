#include <iostream>

#ifdef TEST_FILE_SOLARLESSIRBUTTONCLICK
#include "inc/irSignalValidationTest.hpp"
#elif defined(TEST_FILE_SOLARCHARGE)
#include "inc/batteryChargeMonitoringTest.hpp"
#elif defined(TEST_FILE_PUSHANDMEAS)
#include "inc/batteryVoltageAndButtonTest.hpp"
#endif

int main(int argc, char **argv) {
#ifdef TEST_FILE_SOLARLESSIRBUTTONCLICK
    IrSignalValidationTest button_click_test;
    button_click_test.runTest();
#elif defined(TEST_FILE_SOLARCHARGE)
    BatteryChargeMonitoringTest solar_charge_test;
    solar_charge_test.runTest();
#elif defined(TEST_FILE_PUSHANDMEAS)
    BatteryVoltageAndButtonTest push_and_meas_test;
    push_and_meas_test.runTest();
#else
    std::cerr << "Geçerli bir test dosyası belirtilmedi." << std::endl;
    return EXIT_FAILURE;
#endif

    return EXIT_SUCCESS;
}