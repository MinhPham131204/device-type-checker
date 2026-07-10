#include <jni.h>
#include <string>
#include "json.hpp"

#include "../detectors/emulator/emu_checker.h"

using json = nlohmann::json;

std::string analyzeRisk(int suspicious) {
    if (suspicious > 2) {
        return "HIGH";
    } else if (suspicious > 0) {
        return "LOW";
    }

    return "SAFE";
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_application_devicechecker_jni_NativeCore_analyzeEmulatorRisk(JNIEnv *env, jobject thiz) {

    // init JSON object
    json detailJson;
    detailJson["module"] = "EMULATOR";

    EmulatorChecker checker;
    std::vector<std::string> evidences;
    checker.analyzeRiskLevel(evidences); // pass reference vector to save in log

    detailJson["evidences"] = evidences;

    detailJson["riskLevel"] = analyzeRisk(evidences.size());

    // Convert JSON object to string
    std::string finalJsonString = detailJson.dump();

    // convert string to jstring
    return env->NewStringUTF(finalJsonString.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_application_devicechecker_jni_NativeCore_analyzeRootRisk(JNIEnv *env, jobject thiz) {

    json detailJson;
    detailJson["module"] = "ROOT";

    RootChecker checker;
    std::vector<std::string> evidences;
    checker.analyzeRiskLevel(evidences);

    detailJson["evidences"] = evidences;

    detailJson["riskLevel"] = analyzeRisk(evidences.size());

    std::string finalJsonString = detailJson.dump();

    return env->NewStringUTF(finalJsonString.c_str());
}