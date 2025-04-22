cmake_minimum_required(VERSION 3.25)

project(remote_tester)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.9.0/gcc_arm64/lib/cmake") # kendi setup'ına göre ayarla
find_package(Qt6 REQUIRED COMPONENTS Core)

find_library(WIRINGPI_LIB wiringPi)
if (WIRINGPI_LIB)
    message(STATUS "Found wiringPi: ${WIRINGPI_LIB}")
else()
    message(FATAL_ERROR "wiringPi library not found. Please install it.")
endif()

if (NOT DEFINED TEST_FILE)
# solarlessIrButtonClick
# solarCharge
# pushAndMeas
message(FATAL_ERROR "Testi içeren kaynak dosyasının adını belirtin\nÖrneğin: -DTEST_FILE=solarlessIrButtonClick")
endif()

if (TEST_FILE STREQUAL "solarlessIrButtonClick")
    add_compile_definitions(TEST_FILE_SOLARLESSIRBUTTONCLICK)
elseif (TEST_FILE STREQUAL "solarCharge")
    add_compile_definitions(TEST_FILE_SOLARCHARGE)
elseif (TEST_FILE STREQUAL "pushAndMeas")
    add_compile_definitions(TEST_FILE_PUSHANDMEAS)
else()
    message(FATAL_ERROR "belirtilen test dosyası cmake build'inde bulunamadı\nGeçerli dosyalar: solarlessIrButtonClick, solarCharge")
endif()

set(PROJECT_SOURCES main.cpp
            src/${TEST_FILE}.cpp
            src/ina238.cpp
            src/irManager.cpp
            src/servoController.cpp

            inc/ina238.hpp
            inc/ina238config.hpp
            inc/irManager.hpp
            inc/servoController.hpp
            inc/${TEST_FILE}.hpp
            )

add_executable(remote_tester ${PROJECT_SOURCES})

target_include_directories(remote_tester PRIVATE inc)

target_link_libraries(remote_tester PRIVATE ${WIRINGPI_LIB} Qt6::Core)

