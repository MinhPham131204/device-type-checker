#pragma once

#include <vector>
#include <string>

namespace CheckTelephony {

    /**
     * Check telephony system properties. (not required READ_PHONE_STATE permission).
     */
    bool hasSuspiciousTelephonyProperties(std::vector<std::string>& evidences);

    /**
     * Check telephony data (IMEI, IMSI, Phone number) if provided by the Client application.
     */
    bool hasSuspiciousTelephonyData(const std::string& phoneNumber,
                                    const std::string& imei,
                                    const std::string& imsi,
                                    std::vector<std::string>& evidences);

}