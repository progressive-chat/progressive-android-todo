#pragma once
#include <string>
#include <cstdint>

std::string roomId;(const std::string& json);
std::string name;              // display name(const std::string& json);
std::string avatarUrl;(const std::string& json);
std::string lastMessage;       // preview text(const std::string& json);
std::string lastSender;(const std::string& json);
std::string section;           // "Favourites", "Directs", "Rooms", "Spaces", "Invites", "Low Priority"(const std::string& json);
std::string assignRoomSection(const RoomListItem& room);(const std::string& json);
std::string std(const std::string& json);
std::string vector<RoomListItem> searchRoomList(const std(const std::string& json);
std::string vector<RoomListItem>& rooms, const std(const std::string& json);
std::string string& query);(const std::string& json);
std::string roomListLayoutToJson(const RoomListLayout& layout);(const std::string& json);
std::string formatRoomListItem(const RoomListItem& room);(const std::string& json);
std::string getBadgeText(const RoomListItem& room, int maxDisplay = 99);(const std::string& json);
std::string badgeText;     // "3", "99+", or ""(const std::string& json);
std::string notificationStateToJson(const NotificationState& state);(const std::string& json);
