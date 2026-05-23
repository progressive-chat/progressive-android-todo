#pragma once
#include <string>
#include <cstdint>

std::string deviceId;(const std::string& json);
std::string displayName;(const std::string& json);
std::string lastSeenIp;(const std::string& json);
std::string deviceType;      // "Mobile", "Web", "Desktop", "Unknown"(const std::string& json);
std::string applicationName;(const std::string& json);
std::string applicationVersion;(const std::string& json);
std::string operatingSystem;(const std::string& json);
std::string sessionName;(const std::string& json);
std::string DeviceStats parseDeviceList(const std(const std::string& json);
std::string string& apiResponseJson, const std(const std::string& json);
std::string string& currentDeviceId);(const std::string& json);
std::string classifyDeviceType(const std(const std::string& json);
std::string string& userAgent, const std(const std::string& json);
std::string string& clientName);(const std::string& json);
std::string formatDeviceLastSeen(int64_t lastSeenMs);(const std::string& json);
std::string formatDeviceStats(const DeviceStats& stats);(const std::string& json);
std::string managedManagedDeviceInfoToJson(const ManagedDeviceInfo& device);(const std::string& json);
std::string deviceListToJson(const DeviceStats& stats);(const std::string& json);
std::string getDeviceRecommendation(const ManagedDeviceInfo& device);(const std::string& json);
std::string void sortDevices(std(const std::string& json);
std::string vector<ManagedDeviceInfo>& devices, const std(const std::string& json);
std::string string& sortBy);(const std::string& json);
std::string extractDeviceFingerprint(const std(const std::string& json);
std::string string& deviceId, const std(const std::string& json);
std::string string& keysJson);(const std::string& json);
std::string extractDeviceIdentityKey(const std(const std::string& json);
std::string string& deviceId, const std(const std::string& json);
std::string string& keysJson);(const std::string& json);
std::string formatFingerprint(const std(const std::string& json);
std::string string& fingerprint);(const std::string& json);
std::string sessionId;(const std::string& json);
std::string newName;(const std::string& json);
std::string error;(const std::string& json);
std::string SessionRename validateSessionRename(const std(const std::string& json);
std::string string& sessionId, const std(const std::string& json);
std::string string& newName);(const std::string& json);
std::string buildSessionRenameBody(const std(const std::string& json);
std::string string& sessionId, const std(const std::string& json);
std::string string& newName);(const std::string& json);
