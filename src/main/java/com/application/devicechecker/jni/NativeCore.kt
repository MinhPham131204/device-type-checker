package com.application.devicechecker.jni

internal object NativeCore {
    init {
        System.loadLibrary("device-checker")
    }

    external fun analyzeEmulatorRisk(): String

    external fun analyzeRootRisk(): String
}