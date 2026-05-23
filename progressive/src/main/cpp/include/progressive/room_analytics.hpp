#pragma once
#include <string>
#include <cstdint>

std::string userId;(const std::string& json);
std::string displayName;(const std::string& json);
std::string avatarUrl;(const std::string& json);
std::string serverName;        // extracted from @user(const std::string& json);
std::string server(const std::string& json);
std::string eventId;(const std::string& json);
std::string type;              // "join" or "leave"(const std::string& json);
std::string roomId;(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> servers;           // unique servers(const std::string& json);
std::string std(const std::string& json);
std::string unordered_map<std(const std::string& json);
std::string string, std(const std::string& json);
std::string vector<JoinLeaveEvent>> userJoinHistory; // userId → join/leave events(const std::string& json);
std::string std(const std::string& json);
std::string vector<UserStats> filterByServer(const std(const std::string& json);
std::string vector<UserStats>& users, const std(const std::string& json);
std::string string& server);(const std::string& json);
std::string analyticsToJson(const RoomAnalytics& analytics);(const std::string& json);
std::string eventId;(const std::string& json);
std::string roomId;(const std::string& json);
std::string senderId;(const std::string& json);
std::string senderName;(const std::string& json);
std::string body;(const std::string& json);
std::string eventType;   // "m.room.message", "m.room.member", etc.(const std::string& json);
std::string stateKey;    // for membership events(const std::string& json);
std::string membership;  // "join", "leave", "invite"(const std::string& json);
