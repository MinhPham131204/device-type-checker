#include "root_check.h"
#include "checkFileExist/CheckFileExist.h"
#include "checkInstallPkg/CheckInstallPkg.h"
#include "checkOsBuild/CheckCustomBuilds.h"

void RootChecker::checkFileExist(std::vector<std::string> &evidences) {
    CheckFileExist::hasSuBinaries(evidences);
    CheckFileExist::hasRootManagementApps(evidences);
}

void RootChecker::checkInstallPkg(std::vector<std::string> &evidences) {
    CheckPackages::hasRootPackages(evidences);
}

void RootChecker::checkCustomBuilds(std::vector<std::string> &evidences) {
    CheckCustomBuilds::hasTestKeys(evidences);
}

void RootChecker::analyzeRiskLevel(std::vector<std::string> &evidences) {
    checkFileExist(evidences);
    checkCustomBuilds(evidences);
    checkInstallPkg(evidences);
}