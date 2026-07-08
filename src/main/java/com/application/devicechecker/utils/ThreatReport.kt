package com.application.devicechecker.utils

data class ThreatReport(
    val scanTimestamp: Long,
    val action: String, // "ALLOW", "WARN", "BLOCK"
    val details: List<ThreatDetail>,
)

data class ThreatDetail(
    val module: String,       // "EMULATOR"
    val riskLevel: String,    // "HIGH", "LOW", "SAFE"
    val evidences: List<String>
)