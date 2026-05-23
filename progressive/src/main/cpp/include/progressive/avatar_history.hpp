#pragma once
#include <string>
#include <cstdint>

std::string AvatarChangeReason avatarChangeReasonFromString(const std(const std::string& json);
std::string string& s);(const std::string& json);
std::string mxcUrl;(const std::string& json);
std::string eventId;(const std::string& json);
std::string setDate;       // formatted(const std::string& json);
std::string "May 13, 2026"(const std::string& json);
std::string removedDate;   // formatted or "" if active(const std::string& json);
std::string url;           // avatar URL (alias for mxcUrl)(const std::string& json);
std::string setBy;         // userId who set this avatar(const std::string& json);
std::string setAt;         // formatted timestamp string(const std::string& json);
std::string void addChange(const std(const std::string& json);
std::string string& mxcUrl, const std(const std::string& json);
std::string string& eventId, int64_t timestamp);(const std::string& json);
std::string static formatDate(int64_t epochMs);(const std::string& json);
std::string exportJson() const;(const std::string& json);
std::string void trackAvatarChange(const std(const std::string& json);
std::string string& url, const std(const std::string& json);
std::string string& setBy,(const std::string& json);
std::string formatAvatarHistory() const;(const std::string& json);
std::string getPreviousAvatar() const;(const std::string& json);
std::string currentUrl() const;(const std::string& json);
std::string error;(const std::string& json);
std::string JumpToDateTarget parseJumpToDate(const std(const std::string& json);
std::string string& input);(const std::string& json);
std::string formatJumpTarget(const JumpToDateTarget& target);(const std::string& json);
std::string roomId;(const std::string& json);
std::string roomName;(const std::string& json);
std::string canonicalAlias;(const std::string& json);
std::string const std(const std::string& json);
std::string string& query,(const std::string& json);
std::string double fuzzyScore(const std(const std::string& json);
std::string string& query, const std(const std::string& json);
std::string string& candidate);(const std::string& json);
