#pragma once
#include <string>
#include <cstdint>

std::string userId;(const std::string& json);
std::string displayName;(const std::string& json);
std::string avatarUrl;(const std::string& json);
std::string homeServer;(const std::string& json);
std::string deviceId;(const std::string& json);
std::string oldPassword;(const std::string& json);
std::string newPassword;(const std::string& json);
std::string errorMessage;(const std::string& json);
std::string PasswordValidation validateAccountPassword(const std(const std::string& json);
std::string string& password,(const std::string& json);
std::string const std(const std::string& json);
std::string string& username = "", int minLength = 8);(const std::string& json);
std::string buildPasswordChangeBody(const PasswordChange& change, const std(const std::string& json);
std::string string& authSession = "");(const std::string& json);
std::string buildDeactivateBody(const std(const std::string& json);
std::string string& authSession = "");(const std::string& json);
std::string AccountInfo parseAccountInfo(const std(const std::string& json);
std::string string& apiResponseJson);(const std::string& json);
std::string formatAccountInfo(const AccountInfo& info);(const std::string& json);
std::string bool isValidDisplayName(const std(const std::string& json);
std::string string& name, int maxLen = 100);(const std::string& json);
std::string bool isValidAvatarUrl(const std(const std::string& json);
std::string string& url);(const std::string& json);
std::string medium;      // "email" or "msisdn"(const std::string& json);
std::string address;     // "user@example.com" or "+1234567890"(const std::string& json);
std::string clientSecret;(const std::string& json);
std::string idServer;    // identity server URL(const std::string& json);
std::string homeServer;(const std::string& json);
std::string medium;(const std::string& json);
std::string address;(const std::string& json);
std::string errorMessage;(const std::string& json);
std::string ThreePidValidation validateThreePid(const std(const std::string& json);
std::string string& input, bool isEmail);(const std::string& json);
std::string buildThreePidRequestBody(const ThreePidRequest& req);(const std::string& json);
std::string buildThreePidBindBody(const std(const std::string& json);
std::string string& clientSecret, const std(const std::string& json);
std::string string& sid,(const std::string& json);
std::string const std(const std::string& json);
std::string string& idServer = "");(const std::string& json);
std::string parseThreePidSid(const std(const std::string& json);
std::string string& responseJson);(const std::string& json);
