#include "CheckSysProps.h"
#include <sys/system_properties.h>
#include <algorithm>
#include <cctype>

namespace CheckSysProps {

    /**
     * Read value of a System Property at Native layer.
     */
    std::string getProperty(const char* key) {
        char value[PROP_VALUE_MAX] = {0};
        int length = __system_property_get(key, value);
        if (length > 0) {
            return std::string(value);
        }
        return "";
    }

    /**
     * Check whether the target substring exists within a string..
     */
    bool containsIgnoreCase(const std::string& str, const std::string& sub) {
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


    bool hasQemuProps(std::vector<std::string>& evidences) {
        std::string qemu = getProperty("ro.kernel.qemu");
        if (qemu == "1") {
            evidences.push_back("Found exact match: ro.kernel.qemu = 1");
            return true;
        }
        return false;
    }

    bool hasSuspiciousBuildProps(std::vector<std::string>& evidences) {
        bool isSuspicious = false;

        // check ro.product.board (goldfish, unknown,...)
        std::string board = getProperty("ro.product.board");
        if (containsIgnoreCase(board, "goldfish") || containsIgnoreCase(board, "unknown")) {
            evidences.push_back("Suspicious ro.product.board: " + board);
            isSuspicious = true;
        }

        // check ro.hardware (Ví dụ: goldfish, vbox86, ranchu, nox)
        std::string hardware = getProperty("ro.hardware");
        if (containsIgnoreCase(hardware, "goldfish") ||
            containsIgnoreCase(hardware, "vbox86") ||
            containsIgnoreCase(hardware, "ranchu") ||
            containsIgnoreCase(hardware, "nox")) {
            evidences.push_back("Suspicious ro.hardware: " + hardware);
            isSuspicious = true;
        }

        // check ro.product.device (generic, vbox86p, emulator,...)
        std::string device = getProperty("ro.product.device");
        if (containsIgnoreCase(device, "generic") ||
            containsIgnoreCase(device, "vbox86p") ||
            containsIgnoreCase(device, "emulator")) {
            evidences.push_back("Suspicious ro.product.device: " + device);
            isSuspicious = true;
        }

        // check ro.product.model (sdk, Emulator, Android SDK built for x86)
        std::string model = getProperty("ro.product.model");
        if (containsIgnoreCase(model, "sdk") ||
            containsIgnoreCase(model, "emulator") ||
            containsIgnoreCase(model, "android sdk")) {
            evidences.push_back("Suspicious ro.product.model: " + model);
            isSuspicious = true;
        }

        // check ro.product.name (sdk, google_sdk,...)
        std::string name = getProperty("ro.product.name");
        if (containsIgnoreCase(name, "sdk") || containsIgnoreCase(name, "google_sdk")) {
            evidences.push_back("Suspicious ro.product.name: " + name);
            isSuspicious = true;
        }

        return isSuspicious;
    }
}