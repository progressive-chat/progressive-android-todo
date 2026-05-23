#pragma once
#include <string>
#include <cstdint>

std::string userId;(const std::string& json);
std::string displayName;(const std::string& json);
std::string avatarUrl;(const std::string& json);
std::string name;          // display name(const std::string& json);
std::string normalizedName; // normalized for sorting (lowercase, stripped)(const std::string& json);
std::string const std(const std::string& json);
std::string string& roomNameState,      // m.room.name content (empty if not set)(const std::string& json);
std::string const std(const std::string& json);
std::string string& canonicalAlias,     // m.room.canonical_alias content(const std::string& json);
std::string const std(const std::string& json);
std::string string& myUserId,           // current user ID(const std::string& json);
std::string const std(const std::string& json);
std::string string& directUserId,       // DM partner (empty if not DM)(const std::string& json);
std::string const std(const std::string& json);
std::string string& inviterName,        // inviter's display name (for invite rooms)(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& excludedUserIds = {} // users to exclude(const std::string& json);
std::string normalizeRoomName(const std(const std::string& json);
std::string string& name);(const std::string& json);
std::string bool isUniqueDisplayName(const std(const std::string& json);
std::string vector<RoomMember>& members, const std(const std::string& json);
std::string string& displayName);(const std::string& json);
std::string resolveMemberName((const std::string& json);
std::string getEmptyRoomName(bool isDirect, const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& leftMemberNames);(const std::string& json);
std::string roomNameToJson(const RoomName& name);(const std::string& json);
std::string parseRoomNameContent(const std(const std::string& json);
std::string string& contentJson);(const std::string& json);
std::string parseCanonicalAliasContent(const std(const std::string& json);
std::string string& contentJson);(const std::string& json);
