#pragma once
#include <string>
#include <cstdint>

std::string label;           // "(emoji attack)" or empty(const std::string& json);
std::string int countEmojis(const std(const std::string& json);
std::string string& text);(const std::string& json);
std::string int countUniqueEmojis(const std(const std::string& json);
std::string string& text);(const std::string& json);
std::string EmojiCheck checkEmojiAttack(const std(const std::string& json);
std::string string& text, int maxEmojis = 50, int maxUniqueEmojis = 20);(const std::string& json);
std::string inline getEmojiAttackLabel() { return "(emoji attack)"; }(const std::string& json);
std::string label;           // "5 media omitted" or empty(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& mediaTypes,(const std::string& json);
std::string mediaType;       // "image", "video", "file", "text"(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& mediaTypes,(const std::string& json);
std::string formatMediaCollapseLabel(int count);(const std::string& json);
std::string ruleId;(const std::string& json);
std::string ruleType;       // "keyword", "regex", "domain", "sender", "metadata"(const std::string& json);
std::string condition;      // the matching condition/expression(const std::string& json);
std::string description;    // human-readable rule description(const std::string& json);
std::string std(const std::string& json);
std::string unordered_set<std(const std::string& json);
std::string string> explicitAllowed;  // mxc URLs or patterns(const std::string& json);
std::string std(const std::string& json);
std::string unordered_set<std(const std::string& json);
std::string string> explicitBlocked;(const std::string& json);
std::string reason;(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> violatedRules;  // rule IDs that were triggered(const std::string& json);
std::string ContentGuardResult evaluateContent(const std(const std::string& json);
std::string string& contentBody,(const std::string& json);
std::string const std(const std::string& json);
std::string string& senderId,(const std::string& json);
std::string const std(const std::string& json);
std::string string& mxcUrl,(const std::string& json);
std::string getWarningMessage(ContentWarningType type, const std(const std::string& json);
std::string string& customText = "");(const std::string& json);
std::string void addToBlockList(ContentGuardConfig& config, const std(const std::string& json);
std::string string& pattern);(const std::string& json);
std::string void removeFromBlockList(ContentGuardConfig& config, const std(const std::string& json);
std::string string& pattern);(const std::string& json);
