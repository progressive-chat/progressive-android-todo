#include "progressive/room_encryption_check.hpp"
namespace progressive {
bool isRoomEncrypted(const std::string& json) { return json.find("\"algorithm\":\"m.megolm") != std::string::npos; }
std::string getEncryptionAlgorithm(const std::string& json) {
    auto p = json.find("\"algorithm\":\""); if (p == std::string::npos) return "";
    p += 13; auto e = json.find('"', p); return e != std::string::npos ? json.substr(p, e - p) : "";
}
bool requiresEncryptionForFile(const std::string& state, const std::string& mime) { return isRoomEncrypted(state); }
}
