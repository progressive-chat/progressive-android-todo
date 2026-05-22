#pragma once
#include <string>
#include <vector>
namespace progressive {
struct IgnoredUser { std::string userId; int64_t ignoredAtMs=0; };
std::string buildIgnoreRequest(const std::string& userId);
std::vector<IgnoredUser> parseIgnoredUsers(const std::string& json);
bool isUserIgnored(const std::string& json, const std::string& userId);
std::string buildUnignoreRequest(const std::string& userId);
}
