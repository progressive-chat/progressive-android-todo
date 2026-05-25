#pragma once
#include <string>
#include <unordered_map>

namespace progressive {

struct PowerLevelInfo {
    int usersDefault = 0;
    int eventsDefault = 0;
    int stateDefault = 50;
    int inviteLevel = 0;
    int kickLevel = 50;
    int banLevel = 50;
    int redactLevel = 50;
    std::unordered_map<std::string, int> users;
};

PowerLevelInfo parsePowerLevelInfo(const std::string& json);
int getUserLevel(const PowerLevelInfo& pl, const std::string& userId);
bool canUserBan(const PowerLevelInfo& pl, const std::string& userId);
bool canUserKick(const PowerLevelInfo& pl, const std::string& userId);
bool canUserRedact(const PowerLevelInfo& pl, const std::string& userId);
bool canUserInvite(const PowerLevelInfo& pl, const std::string& userId);
bool canUserChangeState(const PowerLevelInfo& pl, const std::string& userId);
bool isUserAdmin(const PowerLevelInfo& pl, const std::string& userId);
std::string formatPowerLevel(int level);
std::string formatUserRole(const PowerLevelInfo& pl, const std::string& userId);

} // namespace progressive
