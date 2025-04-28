#include <iostream>
#include <QApplication>
#include "inc/gui/mainwindow.hpp"

#ifdef TEST_FILE_IRSVT
#include "inc/irSignalValidationTest.hpp"
#elif defined(TEST_FILE_BCMT)
#include "inc/batteryChargeMonitoringTest.hpp"
#elif defined(TEST_FILE_BVABT)
#include "inc/batteryVoltageAndButtonTest.hpp"
#endif

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.show();
    
#ifdef TEST_FILE_IRSVT
    IrSignalValidationTest test;
    QObject::connect(&test, &IrSignalValidationTest::finished, &app, &QCoreApplication::quit, Qt::QueuedConnection);

#elif defined(TEST_FILE_BCMT)
    BatteryChargeMonitoringTest test;
    QObject::connect(&test, &BatteryChargeMonitoringTest::finished, &app, &QCoreApplication::quit, Qt::QueuedConnection);
    
#elif defined(TEST_FILE_BVABT)
    BatteryVoltageAndButtonTest test;
    QObject::connect(&test, &BatteryVoltageAndButtonTest::finished, &app, &QCoreApplication::quit, Qt::QueuedConnection);
    
#else
    std::cerr << "Geçerli bir test dosyası belirtilmedi." << std::endl;
    return EXIT_FAILURE;
#endif

    //test.runTest();
    return app.exec();
}
