#pragma once
#include <string>
#include <cstdint>

std::string userId;        // @user(const std::string& json);
std::string server(const std::string& json);
std::string displayName;   // "Alice"(const std::string& json);
std::string processedText;     // text with mentions resolved(const std::string& json);
std::string ParsedMentions parseMentions(const std(const std::string& json);
std::string string& body, const std(const std::string& json);
std::string string& formattedBody = "");(const std::string& json);
std::string std(const std::string& json);
std::string vector<Mention> extractAtMentions(const std(const std::string& json);
std::string string& text);(const std::string& json);
std::string bool containsMention(const std(const std::string& json);
std::string string& text, const std(const std::string& json);
std::string string& userId);(const std::string& json);
std::string buildUserPill(const std(const std::string& json);
std::string string& userId, const std(const std::string& json);
std::string string& displayName);(const std::string& json);
std::string buildRoomPill(const std(const std::string& json);
std::string string& roomId);(const std::string& json);
std::string buildEventPill(const std(const std::string& json);
std::string string& eventId, const std(const std::string& json);
std::string string& roomId);(const std::string& json);
std::string bool isMatrixPill(const std(const std::string& json);
std::string string& html);(const std::string& json);
std::string stripPills(const std(const std::string& json);
std::string string& html);(const std::string& json);
std::string resolveMentionDisplayName(const std(const std::string& json);
std::string string& userId,(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string pair<std(const std::string& json);
std::string string, std(const std::string& json);
std::string string>>& knownUsers);(const std::string& json);
