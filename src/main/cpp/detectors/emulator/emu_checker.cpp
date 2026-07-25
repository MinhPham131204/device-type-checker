#include "emu_checker.h"
#include "checkSysProps/CheckSysProps.h"
#include "checkFileSys/CheckFileSys.h"
#include "checkTelephony/CheckTelephony.h"

bool EmulatorChecker::checkSysProp(std::vector<std::string> &evidences) {
    bool qemu = CheckSysProps::hasQemuProps(evidences);
    bool build = CheckSysProps::hasSuspiciousBuildProps(evidences);
    return qemu || build;
}

bool EmulatorChecker::checkFileSystem(std::vector<std::string> &evidences) {
    bool geny = CheckFileSys::hasGenymotionFiles(evidences);
    bool qemuPipe = CheckFileSys::hasQemuPipes(evidences);
    bool suspicious = CheckFileSys::hasSuspiciousFiles(evidences);
    return geny || qemuPipe || suspicious;
}

bool EmulatorChecker::checkTelephony(std::vector<std::string> &evidences) {
    bool data = CheckTelephony::hasSuspiciousTelephonyData("", "", "", evidences);
    bool props = CheckTelephony::hasSuspiciousTelephonyProperties(evidences);
    return data || props;
}

void EmulatorChecker::analyzeRiskLevel(std::vector<std::string> &evidences) {
    checkSysProp(evidences);
    checkFileSystem(evidences);
    checkTelephony(evidences);
}