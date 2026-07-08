package com.application.devicechecker.detectors

import android.content.Context
import com.application.devicechecker.utils.ThreatDetail
import com.application.devicechecker.config.SecConfig

abstract class BaseDetector(
    protected val context: Context,
    protected val config: SecConfig
) {
    /**
     * abstract function for all detectors
     */
    abstract fun scan(): ThreatDetail?
}