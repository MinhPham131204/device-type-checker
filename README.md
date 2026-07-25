# Device Type Checker SDK for Android

## Introduction
**Device Type Checker SDK** is a robust, lightweight, and native (C/C++ based) security library designed to protect your Android applications against compromised environments. By leveraging low-level system checks, and JNI bridges, the SDK provides lightning-fast and highly accurate detection of **Rooted devices** and **Emulators**, and **Custom ROMs** via evaluating system properties, file system artifacts, installed packages, and telephony characteristics to generate a comprehensive threat report, making it incredibly difficult for attackers to bypass or spoof.

---

## How to Use

Follow these 3 simple steps to integrate the SDK into your Android project:

### Step 1: Download the SDK
Download the latest `.aar` file in the Releases section on GitHub.

### Step 2: Add to your project
1. Switch your Android Studio project view to **Project**.
2. Copy the downloaded `.aar` file and paste it into your app's `app/libs/` directory. (Create the `libs` folder if it doesn't exist).
3. Open your app-level `build.gradle` (or `build.gradle.kts`) and add the following dependencies:
```kotlin
dependencies {
    // Include the SDK aar file
    implementation(files("libs/DeviceChecker.aar"))
    
    // The SDK uses Gson for JSON serialization
    implementation("com.google.code.gson:gson:2.10.1") 
}
```

### Step 3: Initialize and Scan
In your Application class or MainActivity, use the SDK's builder to initialize the scanner, execute the device scan, and check the results.
```java
import com.application.devicechecker.SecurityGuard;

public class MainActivity extends AppCompatActivity {
  SecurityGuard instance = new SecurityGuard.Builder(this)
          .enableRootDetection(true)
          .enableEmulatorDetection(true)
          .enableHeadlessDetection(false)
          .build();

  // you can check the result by using Log
  // Log.d("AnalyzeRisk", "Threat report: "+ instance.scanDevice());
}
```

## Requirements
* **Minimum SDK Version:** Android 6.0 (API Level 23)
* **Compile SDK Version:** API Level 35
* **Language & JVM:** Kotlin (compatible with JVM Target 11) and Java 11+
* **Permissions:**
    * Basic scanning requires **NO special permissions**.
    * *(Optional)* To enable advanced Telephony checks (IMEI/IMSI matching), your app must hold the `READ_PHONE_STATE` (or `READ_PRIVILEGED_PHONE_STATE` for Android 10+) permission. The SDK will safely fallback if permissions are not granted.

## Release Notes
To see what has changed in recent versions, please read the [CHANGELOG](CHANGELOG.md).