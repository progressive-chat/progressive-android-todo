#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace progressive {

struct OlmSessionInfo {
    std::string sessionId;
    std::string senderKey;
    std::string claimedKey;
    int64_t creationTimeMs = 0;
    int64_t lastUsedMs = 0;
    int messageCount = 0;
    bool isInbound = true;
};

// Parse Olm session from account data / key backup
OlmSessionInfo parseOlmSession(const std::string& json);

// Format session info for debug display
std::string formatOlmSession(const OlmSessionInfo& session);

// Check if session is stale (> 7 days unused)
bool isOlmSessionStale(const OlmSessionInfo& session, int maxAgeDays = 7);

// Build session ID from sender key
std::string buildOlmSessionId(const std::string& senderKey, const std::string& chainIndex = "0");

// Format fingerprint for display (4-char groups)
std::string formatKeyFingerprint(const std::string& key, int groupSize = 4);

// Validate olm message format
bool isValidOlmMessage(const std::string& messageJson);

} // namespace progressive
