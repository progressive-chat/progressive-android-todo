#pragma once
#include <string>
#include <cstdint>

std::string id;                    // UUID(const std::string& json);
std::string note;                  // Alarm note / label(const std::string& json);
std::string ringtoneUri;          // Android content(const std::string& json);
std::string // URI for ringtone(const std::string& json);
std::string preActionParam;       // City for weather, URL for news, text for reminder(const std::string& json);
std::string createAlarm(const std(const std::string& json);
std::string string& agentText);(const std::string& json);
std::string void snoozeAlarm(const std(const std::string& json);
std::string string& id, int minutes);(const std::string& json);
std::string void dismissAlarm(const std(const std::string& json);
std::string string& id);(const std::string& json);
std::string void setRingtone(const std(const std::string& json);
std::string string& id, const std(const std::string& json);
std::string string& uri);(const std::string& json);
std::string void deleteAlarm(const std(const std::string& json);
std::string string& id);(const std::string& json);
std::string Alarm parseAgentText(const std(const std::string& json);
std::string string& text) const;(const std::string& json);
std::string alarmsToJson() const;(const std::string& json);
std::string void loadAlarmsFromJson(const std::string& json);
std::string generateId() const;(const std::string& json);
std::string int parseMinutes(const std(const std::string& json);
std::string string& s) const;(const std::string& json);
std::string int parseHours(const std(const std::string& json);
std::string string& s) const;(const std::string& json);
std::string int parseTime(const std(const std::string& json);
std::string string& s, int& hour, int& minute) const;(const std::string& json);
