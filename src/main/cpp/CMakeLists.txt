cmake_minimum_required(VERSION 3.22.1)

project("device-checker")

add_library(
        ${CMAKE_PROJECT_NAME}

        SHARED

        core/native_bridge.cpp

        detectors/emulator/emu_checker.cpp

        detectors/emulator/checkFileSys/CheckFileSys.cpp

        detectors/emulator/checkSysProps/CheckSysProps.cpp

        detectors/emulator/checkTelephony/CheckTelephony.cpp
        
        detectors/root_check/root_check.cpp

        detectors/root_check/checkFileExist/CheckFileExist.cpp

        detectors/root_check/checkInstallPkg/CheckInstallPkg.cpp

        detectors/root_check/checkOsBuild/CheckCustomBuilds.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "-Wl,-z,max-page-size=16384")

# Link to standard Android lib (logcat)
find_library(log-lib log)
target_link_libraries(${CMAKE_PROJECT_NAME} ${log-lib})