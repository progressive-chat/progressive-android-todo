#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace progressive {

struct ThreePidRequest {
    std::string clientSecret;
    std::string idServer;
    std::string idAccessToken;
    std::string sid;            // session ID from server
};

struct ThreePidBinding {
    std::string medium;         // "email" or "msisdn"
    std::string address;
    bool bound = false;
};

// Build 3PID add request (email/phone to account)
std::string build3pidAddRequest(const std::string& clientSecret, const std::string& sid);

// Build 3PID bind request
std::string build3pidBindRequest(const ThreePidBinding& binding);

// Parse 3PID list response
std::vector<ThreePidBinding> parseThreePids(const std::string& json);

// Build password change request
std::string buildPasswordChangeRequest(const std::string& oldPassword, const std::string& newPassword,
                                         bool logoutDevices = true);

// Build deactivate account request
std::string buildDeactivateRequest(const std::string& authJson = "");

// Build whoami request (empty body)
std::string buildWhoamiRequest();

} // namespace progressive
