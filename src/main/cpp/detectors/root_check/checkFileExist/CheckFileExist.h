#pragma once

#include <vector>
#include <string>

namespace CheckFileExist {
    /**
     * Check the existence of 'su' (superuser) binary file.
     */
    void hasSuBinaries(std::vector<std::string>& evidences);

    /**
     * Check for files, folders, or popular root management apps (Magisk, SuperSU).
     */
    void hasRootManagementApps(std::vector<std::string>& evidences);
};
