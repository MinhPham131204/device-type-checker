#pragma once

#include <vector>
#include <string>

namespace CheckPackages {

    /**
     * Check the existence of root management application packages.
     */
    void hasRootPackages(std::vector<std::string>& evidences);
}