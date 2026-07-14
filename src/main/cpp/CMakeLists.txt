cmake_minimum_required(VERSION 3.22.1)

project("device-checker")

add_library(
        ${CMAKE_PROJECT_NAME}

        SHARED

        core/native_bridge.cpp

        detectors/emulator/checkFileSys/CheckFileSys.cpp

        detectors/emulator/checkSysProps/CheckSysProps.cpp

        detectors/emulator/checkTelephony/CheckTelephony.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)

# Link to standard Android lib (logcat)
find_library(log-lib log)
target_link_libraries(${CMAKE_PROJECT_NAME} ${log-lib})