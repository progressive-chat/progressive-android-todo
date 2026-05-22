#pragma once
#include <string>
#include <vector>

namespace progressive {

// Format device key for display (groups of 4)
std::string formatDeviceKeyFingerprint(const std::string& key);

// Format recovery key with spaces
std::string formatRecoveryKey(const std::string& rawKey);

// Validate recovery key format
bool isValidRecoveryKey(const std::string& key);

// Parse key backup version from JSON
std::string parseKeyBackupVersion(const std::string& json);

} // namespace progressive
