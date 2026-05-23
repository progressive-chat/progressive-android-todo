#pragma once
#include <string>
#include <cstdint>

std::string globToRegex(const std(const std::string& json);
std::string string& glob);(const std::string& json);
std::string bool hasSpecialGlobChar(const std(const std::string& json);
std::string string& pattern);(const std::string& json);
std::string const std(const std::string& json);
std::string string& eventJson,(const std::string& json);
std::string const std(const std::string& json);
std::string string& key,(const std::string& json);
std::string const std(const std::string& json);
std::string string& pattern(const std::string& json);
std::string extractJsonField(const std(const std::string& json);
std::string string& json, const std(const std::string& json);
std::string string& fieldPath);(const std::string& json);
std::string bool simpleRegexMatch(const std(const std::string& json);
std::string string& text, const std(const std::string& json);
std::string string& regexPattern);(const std::string& json);
std::string bool simpleRegexContainsMatch(const std(const std::string& json);
std::string string& text, const std(const std::string& json);
std::string string& regexPattern);(const std::string& json);
std::string kind;        // "event_match", "room_member_count", "sender_notification_permission"(const std::string& json);
std::string key;         // for event_match(const std::string& json);
std::string "content.body", "sender", "room_id", "type"(const std::string& json);
std::string pattern;     // glob pattern(const std::string& json);
std::string const std(const std::string& json);
std::string string& eventJson(const std::string& json);
std::string pushConditionToJson(const EventPushCondition& condition);(const std::string& json);
std::string ruleId;(const std::string& json);
std::string pattern;                     // glob pattern for content rules(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> actions;        // "notify", "dont_notify", "coalesce", "highlight"(const std::string& json);
std::string notificationSound;           // "default" or custom sound name(const std::string& json);
std::string EventPushRule parseEventPushRule(const std::string& json);
std::string EventPushRule setEventPushRuleSound(const EventPushRule& rule, const std(const std::string& json);
std::string string& sound);(const std::string& json);
std::string pushRuleToJson(const EventPushRule& rule);(const std::string& json);
std::string bool caseInsensitiveFind(const std(const std::string& json);
std::string string& text, const std(const std::string& json);
std::string string& search);(const std::string& json);
std::string bool evaluateDisplayNameCondition(const std(const std::string& json);
std::string string& eventJson, const std(const std::string& json);
std::string string& displayName);(const std::string& json);
