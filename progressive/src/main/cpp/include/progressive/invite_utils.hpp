#pragma once
#include <string>
#include <cstdint>

std::string roomId;(const std::string& json);
std::string roomName;(const std::string& json);
std::string roomAvatarUrl;(const std::string& json);
std::string inviterName;(const std::string& json);
std::string inviterId;(const std::string& json);
std::string errorMessage;(const std::string& json);
std::string InviteInfo parseInviteInfo(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& stateEventsJson);(const std::string& json);
std::string const std(const std::string& json);
std::string string& inviteeId,(const std::string& json);
std::string const std(const std::string& json);
std::string string& myUserId,(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& currentMembers,(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& bannedUsers,(const std::string& json);
std::string const std(const std::string& json);
std::string string& reason,(const std::string& json);
std::string buildInviteBody(const std(const std::string& json);
std::string string& userId, const std(const std::string& json);
std::string string& reason = "");(const std::string& json);
std::string buildThreePidInviteBody(const std(const std::string& json);
std::string string& idServer,(const std::string& json);
std::string const std(const std::string& json);
std::string string& medium, const std(const std::string& json);
std::string string& address);(const std::string& json);
std::string formatInvitePreview(const InviteInfo& info);(const std::string& json);
std::string roomId;(const std::string& json);
std::string reason;(const std::string& json);
std::string buildKnockBody(const std(const std::string& json);
std::string string& reason = "");(const std::string& json);
std::string formatKnockReason(const std(const std::string& json);
std::string string& reason);(const std::string& json);
