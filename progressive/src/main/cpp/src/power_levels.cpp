#include "progressive/power_levels.hpp"
#include <sstream>

namespace progressive {

PowerLevels parsePowerLevels(const std::string& json) {
    PowerLevels pl;
    auto extractInt = [&](const std::string& key) -> int {
        auto p = json.find("\"" + key + "\":");
        if (p == std::string::npos) return -1;
        p += key.size() + 2;
        while (p < json.size() && json[p] == ' ') p++;
        try { return std::stoi(json.substr(p)); } catch(...) { return -1; }
    };
    
    if (extractInt("ban") >= 0) pl.ban = extractInt("ban");
    if (extractInt("invite") >= 0) pl.invite = extractInt("invite");
    if (extractInt("kick") >= 0) pl.kick = extractInt("kick");
    if (extractInt("redact") >= 0) pl.redact = extractInt("redact");
    if (extractInt("state_default") >= 0) pl.stateDefault = extractInt("state_default");
    if (extractInt("events_default") >= 0) pl.eventsDefault = extractInt("events_default");
    if (extractInt("users_default") >= 0) pl.usersDefault = extractInt("users_default");
    
    // Parse users
    auto usersPos = json.find("\"users\"");
    if (usersPos != std::string::npos) {
        auto objStart = json.find('{', usersPos);
        if (objStart != std::string::npos) {
            size_t pos = objStart + 1;
            while (pos < json.size()) {
                auto keyStart = json.find('"', pos);
                if (keyStart == std::string::npos || keyStart >= json.find('}', objStart)) break;
                auto keyEnd = json.find('"', keyStart + 1);
                if (keyEnd == std::string::npos) break;
                auto valStart = json.find(':', keyEnd);
                if (valStart == std::string::npos) break;
                valStart++;
                while (valStart < json.size() && json[valStart] == ' ') valStart++;
                try {
                    pl.users[json.substr(keyStart + 1, keyEnd - keyStart - 1)] = std::stoi(json.substr(valStart));
                } catch(...) {}
                pos = valStart + 1;
            }
        }
    }
    
    // Parse events
    auto eventsPos = json.find("\"events\"");
    if (eventsPos != std::string::npos) {
        auto objStart = json.find('{', eventsPos);
        if (objStart != std::string::npos) {
            size_t pos = objStart + 1;
            while (pos < json.size()) {
                auto keyStart = json.find('"', pos);
                if (keyStart == std::string::npos || keyStart >= json.find('}', objStart)) break;
                auto keyEnd = json.find('"', keyStart + 1);
                if (keyEnd == std::string::npos) break;
                auto valStart = json.find(':', keyEnd);
                if (valStart == std::string::npos) break;
                valStart++;
                while (valStart < json.size() && json[valStart] == ' ') valStart++;
                try {
                    pl.events[json.substr(keyStart + 1, keyEnd - keyStart - 1)] = std::stoi(json.substr(valStart));
                } catch(...) {}
                pos = valStart + 1;
            }
        }
    }
    
    return pl;
}

int getUserPowerLevel(const PowerLevels& pl, const std::string& userId) {
    auto it = pl.users.find(userId);
    return it != pl.users.end() ? it->second : pl.usersDefault;
}

bool canSendStateEvent(const PowerLevels& pl, const std::string& userId, const std::string& eventType) {
    int userPl = getUserPowerLevel(pl, userId);
    auto it = pl.events.find(eventType);
    int required = it != pl.events.end() ? it->second : pl.stateDefault;
    return userPl >= required;
}

bool canSendMessage(const PowerLevels& pl, const std::string& userId) {
    return getUserPowerLevel(pl, userId) >= pl.eventsDefault;
}

bool canRedact(const PowerLevels& pl, const std::string& userId) {
    return getUserPowerLevel(pl, userId) >= pl.redact;
}

bool canBan(const PowerLevels& pl, const std::string& userId) {
    return getUserPowerLevel(pl, userId) >= pl.ban;
}

bool canInvite(const PowerLevels& pl, const std::string& userId) {
    return getUserPowerLevel(pl, userId) >= pl.invite;
}

bool canKick(const PowerLevels& pl, const std::string& userId) {
    return getUserPowerLevel(pl, userId) >= pl.kick;
}

bool canChangePowerLevels(const PowerLevels& pl, const std::string& userId) {
    return getUserPowerLevel(pl, userId) >= pl.stateDefault;
}

std::string buildPowerLevelsContent(const PowerLevels& pl) {
    std::ostringstream os;
    os << "{";
    os << R"("ban":)" << pl.ban;
    os << R"(,"invite":)" << pl.invite;
    os << R"(,"kick":)" << pl.kick;
    os << R"(,"redact":)" << pl.redact;
    os << R"(,"state_default":)" << pl.stateDefault;
    os << R"(,"events_default":)" << pl.eventsDefault;
    os << R"(,"users_default":)" << pl.usersDefault;
    os << R"(,"users":{)";
    bool first = true;
    for (const auto& [uid, level] : pl.users) {
        if (!first) os << ","; first = false;
        os << R"(")" << uid << R"(":)" << level;
    }
    os << "}";
    os << "}";
    return os.str();
}

std::string buildPowerLevelChange(const std::string& userId, int newLevel) {
    std::ostringstream os;
    os << R"({"users":{")" << userId << R"(":)" << newLevel << "}}";
    return os.str();
}

} // namespace progressive
