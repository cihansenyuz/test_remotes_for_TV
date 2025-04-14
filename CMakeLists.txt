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

set(PROJECT_SOURCES main.cpp
            src/solarlessIrButtonClick.cpp
            src/ina238.cpp
            src/irManager.cpp
            src/servoController.cpp

            inc/ina238.hpp
            inc/irManager.hpp
            inc/servoController.hpp
            inc/solarlessIrButtonClick.hpp
            )

add_executable(remote_tester ${PROJECT_SOURCES})

target_include_directories(remote_tester PRIVATE inc)

target_link_libraries(remote_tester ${WIRINGPI_LIB})