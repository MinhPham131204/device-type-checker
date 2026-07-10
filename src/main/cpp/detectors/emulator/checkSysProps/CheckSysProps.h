#pragma once

#include <vector>
#include <string>

class CheckSysProps {

    /**
     * Check specific flags of QEMU (Android Studio's core emulator).
     */
    bool hasQemuProps(std::vector<std::string>& evidences);

    /**
     * check Build Characteristics based on OWASP MASTG's list of emulator detection methods.
     */
    bool hasSuspiciousBuildProps(std::vector<std::string>& evidences);
};