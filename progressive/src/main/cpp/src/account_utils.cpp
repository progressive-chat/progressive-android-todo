#include "progressive/account_utils.hpp"
#include <sstream>

namespace progressive {

std::string build3pidAddRequest(const std::string& clientSecret, const std::string& sid) {
    std::ostringstream os;
    os << R"({"client_secret":")" << clientSecret << R"(",)";
    os << R"("sid":")" << sid << R"(")";
    os << "}";
    return os.str();
}

std::string build3pidBindRequest(const ThreePidBinding& b) {
    std::ostringstream os;
    os << R"({"three_pid_creds":{)";
    os << R"("client_secret":"...",)";
    os << R"("id_server":")" << b.medium << R"(",)";
    os << R"("sid":"...")";
    os << "}";
    os << R"(,"bind":true)";
    os << "}";
    return os.str();
}

std::vector<ThreePidBinding> parseThreePids(const std::string& json) {
    std::vector<ThreePidBinding> pids;
    size_t pos = 0;
    while (pos < json.size()) {
        auto medPos = json.find("\"medium\":\"", pos);
        if (medPos == std::string::npos) break;
        medPos += 10;
        auto medEnd = json.find('"', medPos);
        if (medEnd == std::string::npos) break;
        
        ThreePidBinding b;
        b.medium = json.substr(medPos, medEnd - medPos);
        
        auto addrPos = json.find("\"address\":\"", medEnd);
        if (addrPos != std::string::npos && addrPos - medEnd < 200) {
            addrPos += 11;
            auto addrEnd = json.find('"', addrPos);
            if (addrEnd != std::string::npos) b.address = json.substr(addrPos, addrEnd - addrPos);
        }
        
        b.bound = json.find("\"bound\":true", medEnd) != std::string::npos;
        pids.push_back(b);
        pos = medEnd + 1;
    }
    return pids;
}

std::string buildPasswordChangeRequest(const std::string& oldPw, const std::string& newPw,
                                         bool logoutDevices) {
    std::ostringstream os;
    os << "{";
    os << R"("new_password":")" << newPw << R"(")";
    if (!oldPw.empty()) {
        os << R"(,"auth":{"type":"m.login.password",)";
        os << R"("identifier":{"type":"m.id.user","user":"..."},)";
        os << R"("password":")" << oldPw << R"("})";
    }
    os << R"(,"logout_devices":)" << (logoutDevices ? "true" : "false");
    os << "}";
    return os.str();
}

std::string buildDeactivateRequest(const std::string& authJson) {
    if (!authJson.empty()) return R"({"erase":true,)" + authJson + "}";
    return R"({"erase":true})";
}

std::string buildWhoamiRequest() { return "{}"; }

} // namespace progressive
