#include "progressive/olm_session_utils.hpp"
#include <sstream>
#include <chrono>
#include <algorithm>

namespace progressive {

OlmSessionInfo parseOlmSession(const std::string& json) {
    OlmSessionInfo s;
    auto extract = [&](const std::string& key) -> std::string {
        auto p = json.find("\"" + key + "\":\"");
        if (p == std::string::npos) return "";
        p += key.size() + 4;
        auto e = json.find('"', p);
        if (e == std::string::npos) return "";
        return json.substr(p, e - p);
    };
    s.sessionId = extract("session_id");
    s.senderKey = extract("sender_key");
    s.claimedKey = extract("claimed_key");
    return s;
}

std::string formatOlmSession(const OlmSessionInfo& s) {
    std::ostringstream os;
    os << "Session " << s.sessionId << " [" << (s.isInbound ? "inbound" : "outbound") << "]";
    os << " messages:" << s.messageCount;
    return os.str();
}

bool isOlmSessionStale(const OlmSessionInfo& s, int maxAgeDays) {
    int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    return (now - s.lastUsedMs) > (maxAgeDays * 86400000LL);
}

std::string buildOlmSessionId(const std::string& senderKey, const std::string& chainIndex) {
    return senderKey + "|" + chainIndex;
}

std::string formatKeyFingerprint(const std::string& key, int groupSize) {
    std::ostringstream os;
    for (size_t i = 0; i < key.size(); i++) {
        if (i > 0 && i % groupSize == 0) os << " ";
        os << (char)toupper(key[i]);
    }
    return os.str();
}

bool isValidOlmMessage(const std::string& json) {
    return json.find("\"type\":") != std::string::npos &&
           (json.find("\"ciphertext\"") != std::string::npos ||
            json.find("\"body\"") != std::string::npos);
}

} // namespace progressive
