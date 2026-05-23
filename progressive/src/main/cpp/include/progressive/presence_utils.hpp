#pragma once
#include <string>
#include <cstdint>

std::string parsePresenceEvent(const std::string& json);
std::string buildPresenceUpdate(const std::string& json);
std::string getUserStatus(const std::string& json);
std::string formatLastSeen(const std::string& json);
std::string isUserOnline(const std::string& json);
