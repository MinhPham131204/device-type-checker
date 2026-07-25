package com.application.devicechecker

import android.content.Context
import com.application.devicechecker.config.SecConfig
import com.application.devicechecker.detectors.BaseDetector
import com.application.devicechecker.detectors.EmulatorDetector
import com.application.devicechecker.detectors.RootDetector
import com.application.devicechecker.utils.ThreatDetail
import com.application.devicechecker.utils.ThreatReport
import com.google.gson.GsonBuilder

class SecurityGuard private constructor(
    private val context: Context,
    private val config: SecConfig
) {

    // Singleton pattern => ensure init only once
    companion object {
        @Volatile
        private var INSTANCE: SecurityGuard? = null

        fun getInstance(): SecurityGuard {
            return INSTANCE ?: throw IllegalStateException("SecurityGuard SDK has not been initialized. Call Builder.build() first.")
        }
    }

    private val detectors: List<BaseDetector> = listOf(
        RootDetector(context, config),
        EmulatorDetector(context, config),
    )

    // Executable function
    fun scanDevice(): String {
        val detailsList = mutableListOf<ThreatDetail>()
        var risk = false

        for (detector in detectors) {
            val detail = detector.scan()
            if (detail != null) {
                if(detail.evidences.isNotEmpty() && !risk) {
                    risk = true
                }
                detailsList.add(detail)
            }
        }

        val action = when {
            risk -> "BLOCK"
            else -> "ALLOW"
        }

        val report = ThreatReport(
            scanTimestamp = System.currentTimeMillis(),
            action = action,
            details = detailsList
        )

        val gson = GsonBuilder().setPrettyPrinting().create()

        return gson.toJson(report)
    }

    // Nested Builder Class - Joshua Bloch
    class Builder(private val context: Context) {
        // Giá trị mặc định
        private var rootEnabled = true
        private var emulatorEnabled = true
        private var headlessEnabled = false
        private var threshold = 0.8f

        fun enableRootDetection(enable: Boolean) = apply { this.rootEnabled = enable }

        fun enableEmulatorDetection(enable: Boolean) = apply { this.emulatorEnabled = enable }

        fun enableHeadlessDetection(enable: Boolean) = apply { this.headlessEnabled = enable }

        fun setRiskThreshold(score: Float) = apply { this.threshold = score }

        // build(): create config & lock SDK
        fun build(): SecurityGuard {
            val config = SecConfig(
                isRootDetectionEnabled = rootEnabled,
                isEmulatorDetectionEnabled = emulatorEnabled,
            )

            val sdkInstance = SecurityGuard(context.applicationContext, config)
            INSTANCE = sdkInstance

            // call jni here to propagate config
            // NativeCore.initialize(config.isRootDetectionEnabled, ...)

            return sdkInstance
        }
    }
}