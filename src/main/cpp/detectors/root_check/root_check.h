#pragma once

#include <vector>
#include <string>

class RootChecker {
public:
    RootChecker(); // constructor

    ~RootChecker(); // destructor

    /**
     * main function to make a comprehensive analysis to detect emulator.
     */
    void analyzeRiskLevel(std::vector<std::string>& evidences);

private:
    /**
     * check files typically found on rooted devices
     */
    void checkFileExist(std::vector<std::string>& evidences);

    /**
     * Probe for known root manager packages
     */
    void checkInstallPkg(std::vector<std::string>& evidences);

    /**
     * Check signs of test builds and custom ROMs
     */
    void checkCustomBuilds(std::vector<std::string>& evidences);
};