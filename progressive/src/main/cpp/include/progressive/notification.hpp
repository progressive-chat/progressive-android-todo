#pragma once
#include <string>
#include <cstdint>

std::string keyword;        // the word/phrase that triggers notification(const std::string& json);
std::string void addKeyword(const std(const std::string& json);
std::string string& keyword, bool caseSensitive = false);(const std::string& json);
std::string void removeKeyword(const std(const std::string& json);
std::string string& keyword);(const std::string& json);
std::string void setEnabled(const std(const std::string& json);
std::string string& keyword, bool enabled);(const std::string& json);
std::string check(const std(const std::string& json);
std::string string& body) const;(const std::string& json);
std::string exportJson() const;(const std::string& json);
std::string void importJson(const std::string& json);
std::string static toLower(const std(const std::string& json);
std::string string& s);(const std::string& json);
std::string reactorName;      // who reacted(const std::string& json);
std::string reactionEmoji;    // 🚀(const std::string& json);
std::string sourceBody;       // beginning of the source message(const std::string& json);
std::string sourceSenderName; // who wrote the source message(const std::string& json);
std::string formatReactionPreview(const ReactionPreview& reaction);(const std::string& json);
std::string truncateForReactionPreview(const std(const std::string& json);
std::string string& body, int maxLen = 40);(const std::string& json);
