#pragma once
#include <string>

namespace progressive {

// Build account data set request body
std::string buildAccountDataContent(const std::string& type, const std::string& content);

// Parse account data response
std::string parseAccountData(const std::string& json, const std::string& key);

// Build direct messages account data
std::string buildDirectMessagesContent(const std::string& userId, const std::string& roomId);

// Parse ignored users list
std::string parseIgnoredUsers(const std::string& json);

} // namespace progressive
