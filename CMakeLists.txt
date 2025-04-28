cmake_minimum_required(VERSION 3.25)

project(remote_tester)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.7.3/gcc_arm64/lib/cmake") # kendi setup'ına göre ayarla
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

find_library(WIRINGPI_LIB wiringPi)
if (WIRINGPI_LIB)
    message(STATUS "Found wiringPi: ${WIRINGPI_LIB}")
else()
    message(FATAL_ERROR "wiringPi library not found. Please install it.")
endif()

if (NOT DEFINED TEST_FILE)
# irSignalValidationTest
# batteryChargeMonitoringTest
# batteryVoltageAndButtonTest
message(FATAL_ERROR "Testi içeren kaynak dosyasının adını belirtin\nÖrneğin: -DTEST_FILE=irSignalValidationTest")
endif()

if (TEST_FILE STREQUAL "irSignalValidationTest")
    add_compile_definitions(TEST_FILE_IRSVT)
elseif (TEST_FILE STREQUAL "batteryChargeMonitoringTest")
    add_compile_definitions(TEST_FILE_BCMT)
elseif (TEST_FILE STREQUAL "batteryVoltageAndButtonTest")
    add_compile_definitions(TEST_FILE_BVABT)
else()
    message(FATAL_ERROR "belirtilen test dosyası cmake build'inde bulunamadı\nGeçerli dosyalar: irSignalValidationTest, batteryChargeMonitoringTest, batteryVoltageAndButtonTest")
endif()

set(PROJECT_SOURCES main.cpp
            src/${TEST_FILE}.cpp
            src/ina238.cpp
            src/irManager.cpp
            src/servoController.cpp
            src/remotetest.cpp
            
            src/gui/mainwindow.cpp

            inc/${TEST_FILE}.hpp
            inc/ina238.hpp
            inc/ina238config.hpp
            inc/irManager.hpp
            inc/servoController.hpp
            inc/remotetest.hpp

            inc/gui/mainwindow.hpp

            res/ui/mainwindow.ui
            )

add_executable(remote_tester ${PROJECT_SOURCES})

target_include_directories(remote_tester PRIVATE inc)

target_link_libraries(remote_tester PRIVATE ${WIRINGPI_LIB} Qt6::Core Qt6::Widgets)

