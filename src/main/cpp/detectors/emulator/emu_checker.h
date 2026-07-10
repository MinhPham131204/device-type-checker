#pragma once

#include <vector>
#include <string>

/**
 * class EmulatorChecker is used as a Facade
 */
class EmulatorChecker {
public:
    EmulatorChecker(); // constructor

    ~EmulatorChecker(); // destructor

    /**
     * main function to make a comprehensive analysis to detect emulator.
     */
    void analyzeRiskLevel(std::vector<std::string>& evidences);

private:
    /**
     * check System Properties (ro.kernel.qemu, ro.hardware, ro.build.flavor,...)
     */
    bool checkSysProp(std::vector<std::string>& evidences);

    /**
     * check files system (/dev/qemu_pipe, /dev/socket/genyd...)
     */
    bool checkFileSystem(std::vector<std::string>& evidences);

    /**
     * check telephony (FEATURE_TELEPHONY)
     */
    bool checkTelephony(std::vector<std::string>& evidences);
};