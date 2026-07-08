package com.application.devicechecker.detectors

import com.google.gson.Gson
import android.content.Context
import com.application.devicechecker.config.SecConfig
import com.application.devicechecker.jni.NativeCore
import com.application.devicechecker.utils.ThreatDetail

class RootDetector(
    context: Context,
    config: SecConfig
) : BaseDetector(context, config) {

    private val gson = Gson()

    override fun scan(): ThreatDetail? {
        if (!config.isEmulatorDetectionEnabled) return null

        val jsonResult = NativeCore.analyzeRootRisk()

        return gson.fromJson(jsonResult, ThreatDetail::class.java)
    }
}