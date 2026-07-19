#include "CheckCustomBuilds.h"
#include <sys/system_properties.h>

namespace CheckCustomBuilds {

    // helper function
    static std::string getProperty(const char* key) {
        char value[PROP_VALUE_MAX] = {0};
        int length = __system_property_get(key, value);
        if (length > 0) {
            return std::string(value);
        }
        return "";
    }

    void hasTestKeys(std::vector<std::string>& evidences) {
        bool isSuspicious = false;
        std::string buildTags = getProperty("ro.build.tags");

        // check buildTags string contains "test-keys" or not
        if (!buildTags.empty() && buildTags.find("test-keys") != std::string::npos) {
            evidences.push_back("Found Custom Android Build (test-keys): ro.build.tags=" + buildTags);
            isSuspicious = true;
        }
    }

}