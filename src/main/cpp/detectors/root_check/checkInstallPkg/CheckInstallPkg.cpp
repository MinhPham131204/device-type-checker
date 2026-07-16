#include "CheckInstallPkg.h"
#include <unistd.h>

namespace CheckPackages {

    // helper function
    static bool fileExists(const char* path) {
        return access(path, F_OK) == 0;
    }

    void hasRootPackages(std::vector<std::string>& evidences) {

        const char* rootPackages[] = {
                "eu.chainfire.supersu",
                "com.noshufou.android.su",
                "com.koushikdutta.superuser",
                "com.topjohnwu.magisk"
        };

        for (const char* path : rootPackages) {
            if (fileExists(path)) {
                evidences.push_back("Found Root package data directory: " + std::string(path));
            }
        }
    }

}