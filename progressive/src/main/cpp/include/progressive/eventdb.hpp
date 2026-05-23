#pragma once
#include <string>
#include <cstdint>

std::string eventId;(const std::string& json);
std::string roomId;(const std::string& json);
std::string senderId;(const std::string& json);
std::string senderName;(const std::string& json);
std::string timestamp;(const std::string& json);
std::string body;(const std::string& json);
std::string msgType;(const std::string& json);
std::string eventType;(const std::string& json);
std::string relationType;(const std::string& json);
std::string sourceEventId;(const std::string& json);
std::string eventId;(const std::string& json);
std::string topReactions; // JSON array of {key, count, addedByMe}(const std::string& json);
std::string bool open(const std(const std::string& json);
std::string string& dbPath);(const std::string& json);
std::string getContextJson(const std(const std::string& json);
std::string string& eventId) const;(const std::string& json);
std::string std(const std::string& json);
std::string vector<DbEvent> getEvents(const std(const std::string& json);
std::string string& roomId, int limit, int offset) const;(const std::string& json);
std::string void clearRoom(const std(const std::string& json);
std::string string& roomId);(const std::string& json);
