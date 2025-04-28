cmake_minimum_required(VERSION 3.25)

project(remote_tester)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.7.3/gcc_arm64/lib/cmake") # kendi setup'ına göre ayarla
find_package(Qt6 REQUIRED COMPONENTS Widgets)

find_library(WIRINGPI_LIB wiringPi)
if (WIRINGPI_LIB)
    message(STATUS "Found wiringPi: ${WIRINGPI_LIB}")
else()
    message(FATAL_ERROR "wiringPi library not found. Please install it.")
endif()

set(PROJECT_SOURCES main.cpp
            src/irSignalValidationTest.cpp
            src/batteryChargeMonitoringTest.cpp
            src/batteryVoltageAndButtonTest.cpp
            src/ina238.cpp
            src/irManager.cpp
            src/servoController.cpp
            src/remotetest.cpp
            
            src/gui/mainwindow.cpp
            src/gui/hardwaresettings.cpp
            src/gui/IRSVTsettingsdialog.cpp

            inc/irSignalValidationTest.hpp
            inc/batteryChargeMonitoringTest.hpp
            inc/batteryVoltageAndButtonTest.hpp
            inc/ina238.hpp
            inc/ina238config.hpp
            inc/irManager.hpp
            inc/servoController.hpp
            inc/remotetest.hpp
            inc/testfactory.hpp

            inc/gui/mainwindow.hpp
            inc/gui/hardwaresettings.hpp
            inc/gui/testsettingfactory.hpp
            inc/gui/IRSVTsettingsdialog.hpp

            res/ui/mainwindow.ui
            res/ui/hardwaresettings.ui
            res/ui/IRSVTsettingsdialog.ui
            )

add_executable(remote_tester ${PROJECT_SOURCES})

target_include_directories(remote_tester PRIVATE inc)

target_link_libraries(remote_tester PRIVATE ${WIRINGPI_LIB} Qt6::Widgets)

