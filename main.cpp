#include <iostream>
#include <QCoreApplication>

#ifdef TEST_FILE_SOLARLESSIRBUTTONCLICK
#include "inc/irSignalValidationTest.hpp"
#elif defined(TEST_FILE_SOLARCHARGE)
#include "inc/batteryChargeMonitoringTest.hpp"
#elif defined(TEST_FILE_PUSHANDMEAS)
#include "inc/batteryVoltageAndButtonTest.hpp"
#endif

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    
#ifdef TEST_FILE_SOLARLESSIRBUTTONCLICK
    IrSignalValidationTest test;
    QObject::connect(&test, &IrSignalValidationTest::finished, &app, &QCoreApplication::quit, Qt::QueuedConnection);

#elif defined(TEST_FILE_SOLARCHARGE)
    BatteryChargeMonitoringTest test;
    QObject::connect(&test, &BatteryChargeMonitoringTest::finished, &app, &QCoreApplication::quit, Qt::QueuedConnection);
    
#elif defined(TEST_FILE_PUSHANDMEAS)
    BatteryVoltageAndButtonTest push_and_meas_test;
    push_and_meas_test.runTest();
#else
    std::cerr << "Geçerli bir test dosyası belirtilmedi." << std::endl;
    return EXIT_FAILURE;
#endif

    test.runTest();
    return app.exec();
}
