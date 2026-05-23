#pragma once
#include <string>
#include <cstdint>

std::string title;               // Room name or sender name(const std::string& json);
std::string body;                // Message preview(const std::string& json);
std::string ticker;              // Status bar text(const std::string& json);
std::string roomId;              // Which room to open on tap(const std::string& json);
std::string eventId;             // Which event to jump to(const std::string& json);
std::string senderName;          // Who sent the message(const std::string& json);
std::string senderAvatarUrl;     // Avatar to show(const std::string& json);
std::string roomAvatarUrl;       // Room avatar(const std::string& json);
std::string sound;               // "default" or custom URI(const std::string& json);
std::string category;            // "msg", "call", etc.(const std::string& json);
std::string groupKey;            // For grouping multiple notifications(const std::string& json);
std::string inline buildNotificationGroupKey(const std(const std::string& json);
std::string string& roomId) {(const std::string& json);
std::string inline buildNotificationSummary(int totalMessages, int roomCount) {(const std::string& json);
std::string msg = std(const std::string& json);
std::string to_string(totalMessages) + " new message" + (totalMessages > 1 ? "s"(const std::string& json);
std::string "");(const std::string& json);
std::string inline bool matchPushCondition(const std(const std::string& json);
std::string string& fieldValue, const std(const std::string& json);
std::string string& pattern) {(const std::string& json);
std::string fv = fieldValue;(const std::string& json);
std::string pat = pattern;(const std::string& json);
std::string if (pat.find('*') == std(const std::string& json);
std::string string(const std::string& json);
std::string npos && pat.find('?') == std(const std::string& json);
std::string string(const std::string& json);
std::string npos) {(const std::string& json);
std::string return fv.find(pat) != std(const std::string& json);
std::string string(const std::string& json);
std::string npos;(const std::string& json);
std::string regex;(const std::string& json);
std::string search = pat;(const std::string& json);
std::string return fv.find(search) != std(const std::string& json);
std::string string(const std::string& json);
std::string npos;(const std::string& json);
std::string bool isDuplicate(const std(const std::string& json);
std::string string& eventId) {(const std::string& json);
std::string std(const std::string& json);
std::string unordered_set<std(const std::string& json);
std::string string> seen_;(const std::string& json);
