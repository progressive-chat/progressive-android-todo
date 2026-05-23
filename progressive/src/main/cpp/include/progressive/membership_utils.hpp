#pragma once
#include <string>
#include <cstdint>

std::string userId;(const std::string& json);
std::string displayName;(const std::string& json);
std::string avatarUrl;(const std::string& json);
std::string reason;        // ban reason or invite reason(const std::string& json);
std::string userId;(const std::string& json);
std::string displayName;(const std::string& json);
std::string senderId;       // who made the change(const std::string& json);
std::string MemberInfo parseMemberInfo(const std(const std::string& json);
std::string string& stateContentJson, const std(const std::string& json);
std::string string& userId);(const std::string& json);
std::string MemberState parseMemberState(const std(const std::string& json);
std::string string& membershipStr);(const std::string& json);
std::string formatMemberState(MemberState membership);(const std::string& json);
std::string formatMemberStateChange(const MemberStateChange& change);(const std::string& json);
std::string roomId;(const std::string& json);
std::string MemberListInfo parseMemberList(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& apiResponseJson, bool isTruncated);(const std::string& json);
std::string std(const std::string& json);
std::string vector<MemberInfo> searchMembers(const std(const std::string& json);
std::string vector<MemberInfo>& members, const std(const std::string& json);
std::string string& query);(const std::string& json);
std::string void sortMembers(std(const std::string& json);
std::string vector<MemberInfo>& members, const std(const std::string& json);
std::string string& sortBy);(const std::string& json);
std::string memberListToJson(const MemberListInfo& list);(const std::string& json);
std::string const std(const std::string& json);
std::string string& oldName, const std(const std::string& json);
std::string string& newName,(const std::string& json);
std::string const std(const std::string& json);
std::string string& oldAvatar, const std(const std::string& json);
std::string string& newAvatar,(const std::string& json);
