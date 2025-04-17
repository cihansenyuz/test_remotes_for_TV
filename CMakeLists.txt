cmake_minimum_required(VERSION 3.25)

project(remote_tester)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(WIRINGPI_LIB wiringPi)
if (WIRINGPI_LIB)
    message(STATUS "Found wiringPi: ${WIRINGPI_LIB}")
else()
    message(FATAL_ERROR "wiringPi library not found. Please install it.")
endif()

if (NOT DEFINED TEST_FILE)
# irSignalValidationTest
# solarCharge
# batteryVoltageAndButtonTest
message(FATAL_ERROR "Testi içeren kaynak dosyasının adını belirtin\nÖrneğin: -DTEST_FILE=irSignalValidationTest")
endif()

if (TEST_FILE STREQUAL "irSignalValidationTest")
    add_compile_definitions(TEST_FILE_SOLARLESSIRBUTTONCLICK)
elseif (TEST_FILE STREQUAL "solarCharge")
    add_compile_definitions(TEST_FILE_SOLARCHARGE)
elseif (TEST_FILE STREQUAL "batteryVoltageAndButtonTest")
    add_compile_definitions(TEST_FILE_PUSHANDMEAS)
else()
    message(FATAL_ERROR "belirtilen test dosyası cmake build'inde bulunamadı\nGeçerli dosyalar: irSignalValidationTest, solarCharge")
endif()

set(PROJECT_SOURCES main.cpp
            src/${TEST_FILE}.cpp
            src/ina238.cpp
            src/irManager.cpp
            src/servoController.cpp
            src/remotetest.cpp

            inc/ina238.hpp
            inc/ina238config.hpp
            inc/irManager.hpp
            inc/servoController.hpp
            inc/${TEST_FILE}.hpp
            inc/remotetest.hpp
            )

add_executable(remote_tester ${PROJECT_SOURCES})

target_include_directories(remote_tester PRIVATE inc)

target_link_libraries(remote_tester ${WIRINGPI_LIB})