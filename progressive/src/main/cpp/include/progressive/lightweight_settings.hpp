#pragma once
#include <string>
#include <cstdint>

std::string SyncPresence syncPresenceFromString(const std(const std::string& json);
std::string string& s);(const std::string& json);
std::string lightweightSettingsToJson(const LightweightSettings& settings);(const std::string& json);
std::string LightweightSettings lightweightSettingsFromJson(const std::string& json);
std::string bool getSettingBool(const std(const std::string& json);
std::string string& settingsJson, const std(const std::string& json);
std::string string& key, bool defaultVal);(const std::string& json);
std::string setSettingBool(const std(const std::string& json);
std::string string& settingsJson, const std(const std::string& json);
std::string string& key, bool val);(const std::string& json);
std::string getSettingString(const std(const std::string& json);
std::string string& settingsJson, const std(const std::string& json);
std::string string& key, const std(const std::string& json);
std::string string& defaultVal);(const std::string& json);
std::string setSettingString(const std(const std::string& json);
std::string string& settingsJson, const std(const std::string& json);
std::string string& key, const std(const std::string& json);
std::string string& val);(const std::string& json);
