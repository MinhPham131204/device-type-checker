#include "CheckFileSys.h"
#include <unistd.h>

namespace CheckFileSys {

    /**
     * check the existence of a file by using F_OK flag of access() function.
     */
    bool fileExists(const char* path) {
        return access(path, F_OK) == 0;
    }

    bool hasQemuPipes(std::vector<std::string>& evidences) {
        bool isSuspicious = false;

        // List of QEMU artifacts (Android Studio Emulator)
        const char* qemuFiles[] = {
                "/dev/qemu_pipe",
                "/dev/socket/qemud",
                "/sys/qemu_trace",
                "/system/bin/qemu-props",
                "/system/lib/libc_malloc_debug_qemu.so",
                "/system/lib64/libc_malloc_debug_qemu.so"
        };

        for (const char* path : qemuFiles) {
            if (fileExists(path)) {
                evidences.push_back("Found QEMU artifact: " + std::string(path));
                isSuspicious = true;
            }
        }

        return isSuspicious;
    }

    bool hasGenymotionFiles(std::vector<std::string>& evidences) {
        bool isSuspicious = false;

        // List of Genymotion artifacts
        const char* genyFiles[] = {
                "/dev/socket/genyd",
                "/dev/socket/baseband_genyd"
        };

        for (const char* path : genyFiles) {
            if (fileExists(path)) {
                evidences.push_back("Found Genymotion artifact: " + std::string(path));
                isSuspicious = true;
            }
        }

        return isSuspicious;
    }

    bool hasSuspiciousFiles(std::vector<std::string>& evidences) {
        bool isSuspicious = false;

        // List of artifacts from other popular emulators
        const char* otherEmulatorFiles[] = {
                "/dev/goldfish_pipe",            // Goldfish emulator
                "/system/lib/libdroid4x.so",     // Droid4X
                "/system/bin/windroyed",         // Windroy
                "/system/bin/microvirtd",        // MEmu emulator
        };

        for (const char* path : otherEmulatorFiles) {
            if (fileExists(path)) {
                evidences.push_back("Found suspicious Emulator artifact: " + std::string(path));
                isSuspicious = true;
            }
        }

        return isSuspicious;
    }
}