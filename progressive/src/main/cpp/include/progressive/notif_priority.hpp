#pragma once
#include <string>
#include <cstdint>

std::string senderName;(const std::string& json);
std::string body;(const std::string& json);
std::string roomName;(const std::string& json);
std::string roomId;(const std::string& json);
std::string soundUri;         // empty = default(const std::string& json);
std::string category;         // Android notification category(const std::string& json);
std::string formatNotifTitle(const NotifContent& content);(const std::string& json);
std::string formatNotifBody(const NotifContent& content, bool showSender);(const std::string& json);
std::string truncateForNotification(const std(const std::string& json);
std::string string& text, int maxLen = 120);(const std::string& json);
std::string bool isRoomMention(const std(const std::string& json);
std::string string& body);(const std::string& json);
