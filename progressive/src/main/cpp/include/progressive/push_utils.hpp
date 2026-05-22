#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace progressive {

struct PushRule {
    std::string ruleId;
    std::string kind;           // "override", "underride", "content", "sender", "room"
    std::string pattern;
    std::string action;         // "notify", "dont_notify", "coalesce"
    bool highlight = false;
    bool sound = false;
    std::string soundName;
};

// Parse push rules from /pushrules/ response
std::vector<PushRule> parsePushRules(const std::string& json);

// Build push rule content for setting a rule
std::string buildPushRuleContent(const std::string& pattern, const std::string& action,
                                   bool highlight, const std::string& sound = "");

// Check if event matches a push rule
bool matchesPushRule(const PushRule& rule, const std::string& eventContent,
                       const std::string& senderId, const std::string& roomId);

// Get default push actions for a room
std::string getDefaultPushAction(bool isDirect, bool isMuted, bool hasHighlight);

} // namespace progressive
