#pragma once
#include <string>
#include <vector>

namespace progressive {

struct CryptoDeviceInfo {
    std::string deviceId;
    std::string userId;
    std::string deviceName;
    std::vector<std::string> algorithms;  // ["m.olm.v1.curve25519-aes-sha2", "m.megolm.v1.aes-sha2"]
    std::string ed25519Key;               // device signing key
    std::string curve25519Key;            // device encryption key
    bool isVerified = false;
    bool isBlocked = false;
    bool isActive = true;
};

// Parse device info from /keys/query response
CryptoDeviceInfo parseCryptoDeviceInfo(const std::string& deviceId, const std::string& userId,
                                         const std::string& json);

// Format device key for display (truncated fingerprint)
std::string formatDeviceKey(const std::string& key, int truncateLen = 12);

// Check if device supports algorithm
bool deviceSupportsAlgorithm(const CryptoDeviceInfo& d, const std::string& algo);

// Build device list filter
bool isActiveDevice(const CryptoDeviceInfo& d, int64_t inactiveThresholdDays = 30);

// Format device info for user display
std::string formatDeviceInfo(const CryptoDeviceInfo& d);

} // namespace progressive
