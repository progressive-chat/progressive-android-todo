#ifndef PROGRESSIVE_DEVICE_MANAGER_HPP
#define PROGRESSIVE_DEVICE_MANAGER_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace progressive {

// ---- Device Info ----

struct DeviceInfo {
    std::string deviceId;
    std::string displayName;
    std::string lastSeenIp;
    int64_t lastSeenTs = 0;
    int64_t lastSeenAtMs = 0;
    bool isVerified = false;
    bool isCurrentDevice = false;
    bool isInactive = false;     // 90+ days since last activity
    std::string deviceType;      // "Mobile", "Web", "Desktop", "Unknown"
    std::string applicationName;
    std::string applicationVersion;
    std::string operatingSystem;
    std::string sessionName;
};

struct DeviceStats {
    int totalDevices = 0;
    int verifiedDevices = 0;
    int unverifiedDevices = 0;
    int inactiveDevices = 0;
    int currentDeviceIndex = -1;
    std::vector<DeviceInfo> devices;
};

// Parse device list from Matrix /devices API response.
DeviceStats parseDeviceList(const std::string& apiResponseJson, const std::string& currentDeviceId);

// Classify device type from user agent string.
std::string classifyDeviceType(const std::string& userAgent, const std::string& clientName);

// Check if device is inactive (>90 days since last seen).
bool isDeviceInactive(int64_t lastSeenMs, int64_t nowMs = 0);

// Format device last seen as relative time.
std::string formatDeviceLastSeen(int64_t lastSeenMs);

// Format device stats as text for settings display.
std::string formatDeviceStats(const DeviceStats& stats);

// Format device info as JSON.
std::string deviceInfoToJson(const DeviceInfo& device);

// Format device list as JSON.
std::string deviceListToJson(const DeviceStats& stats);

// Get security recommendation for a device.
std::string getDeviceRecommendation(const DeviceInfo& device);

// Sort devices (by name, by last seen, by verification).
void sortDevices(std::vector<DeviceInfo>& devices, const std::string& sortBy);

// ---- Session Rename ----

struct SessionRename {
    std::string sessionId;
    std::string newName;
    bool valid = false;
    std::string error;
};

// Validate a session rename request.
SessionRename validateSessionRename(const std::string& sessionId, const std::string& newName);

// Build session rename request body JSON.
std::string buildSessionRenameBody(const std::string& sessionId, const std::string& newName);

} // namespace progressive

#endif // PROGRESSIVE_DEVICE_MANAGER_HPP
