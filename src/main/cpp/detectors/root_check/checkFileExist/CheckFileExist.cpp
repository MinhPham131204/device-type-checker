#include "CheckFileExist.h"
#include <unistd.h>

namespace CheckFileExist {

    static bool fileExists(const char* path) {
        return access(path, F_OK) == 0;
    }

    void hasSuBinaries(std::vector<std::string>& evidences) {

        const char* suPaths[] = {
                "/sbin/su",
                "/system/bin/su",
                "/system/bin/failsafe/su",
                "/system/xbin/su",
                "/system/xbin/busybox",
                "/system/sd/xbin/su",
                "/data/local/su",
                "/data/local/xbin/su",
                "/data/local/bin/su"
        };

        for (const char* path : suPaths) {
            if (fileExists(path)) {
                evidences.push_back("Found Root binary (su): " + std::string(path));
            }
        }
    }

    void hasRootManagementApps(std::vector<std::string>& evidences) {

        const char* rootAppPaths[] = {
                "/system/app/Superuser.apk",
                "/system/etc/init.d/99SuperSUDaemon",
                "/dev/com.koushikdutta.superuser.daemon/",
                "/system/xbin/daemonsu"
        };

        for (const char* path : rootAppPaths) {
            if (fileExists(path)) {
                evidences.push_back("Found Root management artifact: " + std::string(path));
            }
        }
    }

}