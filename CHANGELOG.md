## [1.0.0] - 2026-07-25

### Added
- **Emulator Detection (`emu-check`)**:
    - Added native checks for emulator system properties (Ex: `ro.kernel.qemu`).
    - Added fast POSIX `access()` checks for QEMU pipes and Genymotion artifacts.
    - Added telephony checks for hardcoded emulator operator names and SIM data.
- **Root Detection (`root-check`)**:
    - Implemented high-speed file system scanning for `su` binaries across known system paths.
    - Added detection for root management applications (Magisk, SuperSU) via file and package data directory checks.
    - Added Custom Build detection by analyzing `ro.build.tags` for `test-keys`.