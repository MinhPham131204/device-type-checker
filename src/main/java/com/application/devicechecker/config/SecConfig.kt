package com.application.devicechecker.config

data class SecConfig internal constructor(
    val isRootDetectionEnabled: Boolean,
    val isEmulatorDetectionEnabled: Boolean
)