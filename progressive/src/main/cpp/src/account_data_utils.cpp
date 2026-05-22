#include "progressive/account_data_utils.hpp"
#include <sstream>

namespace progressive {
std::string buildAccountDataContent(const std::string& type, const std::string& content) { return content; }
std::string parseAccountData(const std::string& json, const std::string& key) {
    auto p = json.find("\"" + key + "\":"); if (p == std::string::npos) return "";
    return json.substr(p); 
}
std::string buildDirectMessagesContent(const std::string& uid, const std::string& rid) {
    return R"({")" + uid + R"(":[")" + rid + R"("]})";
}
std::string parseIgnoredUsers(const std::string& json) {
    auto p = json.find("\"ignored_users\""); if (p == std::string::npos) return "{}";
    return json.substr(p);
}
} // namespace progressive
