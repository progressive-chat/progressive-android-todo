#include "progressive/encryption_key_utils.hpp"
#include <sstream>
#include <algorithm>

namespace progressive {
std::string formatDeviceKeyFingerprint(const std::string& key) {
    std::ostringstream os;
    for (size_t i = 0; i < key.size(); i++) { if (i > 0 && i % 4 == 0) os << " "; os << (char)toupper(key[i]); }
    return os.str();
}
std::string formatRecoveryKey(const std::string& raw) {
    std::ostringstream os;
    for (size_t i = 0; i < raw.size(); i++) { if (i > 0 && i % 4 == 0) os << " "; os << raw[i]; }
    return os.str();
}
bool isValidRecoveryKey(const std::string& key) { return key.size() >= 48; }
std::string parseKeyBackupVersion(const std::string& json) {
    auto p = json.find("\"version\":\""); if (p == std::string::npos) return "";
    p += 11; auto e = json.find('"', p); return e != std::string::npos ? json.substr(p, e - p) : "";
}
} // namespace progressive
