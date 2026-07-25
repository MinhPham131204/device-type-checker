#pragma once

#include <vector>
#include <string>

namespace CheckCustomBuilds {

    /**
     * Check build tags of Android to know this is a custom build or not.
     */
    void hasTestKeys(std::vector<std::string>& evidences);
}