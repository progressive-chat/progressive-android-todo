#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace progressive {

struct PowerLevels {
    int ban = 50;
    int invite = 0;
    int kick = 50;
    int redact = 50;
    int stateDefault = 50;
    int eventsDefault = 0;
    int usersDefault = 0;
    int notifications_room = 50;
    std::unordered_map<std::string, int> users;    // userId → power level
    std::unordered_map<std::string, int> events;   // eventType → required level
};

// Parse m.room.power_levels event content
PowerLevels parsePowerLevels(const std::string& json);

// Get user's power level in a room
int getUserPowerLevel(const PowerLevels& pl, const std::string& userId);

// Check permissions
bool canSendStateEvent(const PowerLevels& pl, const std::string& userId, const std::string& eventType);
bool canSendMessage(const PowerLevels& pl, const std::string& userId);
bool canRedact(const PowerLevels& pl, const std::string& userId);
bool canBan(const PowerLevels& pl, const std::string& userId);
bool canInvite(const PowerLevels& pl, const std::string& userId);
bool canKick(const PowerLevels& pl, const std::string& userId);
bool canChangePowerLevels(const PowerLevels& pl, const std::string& userId);

// Build power levels content to set user's level
std::string buildPowerLevelsContent(const PowerLevels& pl);
std::string buildPowerLevelChange(const std::string& userId, int newLevel);

} // namespace progressive
