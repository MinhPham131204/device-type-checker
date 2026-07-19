#include "CheckTelephony.h"
#include <sys/system_properties.h>
#include <algorithm>
#include <cctype>

namespace CheckTelephony {
    static std::string getProperty(const char* key) {
        char value[PROP_VALUE_MAX] = {0};
        int length = __system_property_get(key, value);
        if (length > 0) {
            return std::string(value);
        }
        return "";
    }

    static bool containsIgnoreCase(const std::string& str, const std::string& sub) {
        if (sub.empty()) return true;
        if (str.empty()) return false;

        auto it = std::search(
                str.begin(), str.end(),
                sub.begin(), sub.end(),
                [](unsigned char ch1, unsigned char ch2) {
                    return std::tolower(ch1) == std::tolower(ch2);
                }
        );
        return it != str.end();
    }

    bool hasSuspiciousTelephonyProperties(std::vector<std::string>& evidences) {
        bool isSuspicious = false;

        // Emulators typically name the network provider "Android".
        std::string operatorName = getProperty("gsm.operator.alpha");
        std::string simOperatorName = getProperty("gsm.sim.operator.alpha");

        if (containsIgnoreCase(operatorName, "android")) {
            evidences.push_back("Suspicious gsm.operator.alpha: " + operatorName);
            isSuspicious = true;
        }

        if (containsIgnoreCase(simOperatorName, "android")) {
            evidences.push_back("Suspicious gsm.sim.operator.alpha: " + simOperatorName);
            isSuspicious = true;
        }

        return isSuspicious;
    }

    bool hasSuspiciousTelephonyData(const std::string& phoneNumber,
                                    const std::string& imei,
                                    const std::string& imsi,
                                    std::vector<std::string>& evidences) {
        bool isSuspicious = false;

        // Check fake Phone Number
        if (phoneNumber == "+15555218135" || phoneNumber == "+1555215554" || phoneNumber == "15555218135") {
            evidences.push_back("Found Emulator hardcoded Phone Number: " + phoneNumber);
            isSuspicious = true;
        }

        // check fake IMEI (1555521...)
        if (imei.length() >= 7 && imei.substr(0, 7) == "1555521") {
            evidences.push_back("Found Emulator hardcoded IMEI prefix: " + imei.substr(0, 7) + "...");
            isSuspicious = true;
        }

        // check fake IMSI (310260000000000...)
        if (imsi.length() >= 15 && imsi.substr(0, 15) == "310260000000000") {
            evidences.push_back("Found Emulator hardcoded IMSI prefix: 310260000000000");
            isSuspicious = true;
        }

        return isSuspicious;
    }

}