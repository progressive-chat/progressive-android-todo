#pragma once
#include <string>
#include <cstdint>

std::string eventId;(const std::string& json);
std::string roomId;(const std::string& json);
std::string roomName;(const std::string& json);
std::string senderName;(const std::string& json);
std::string body;           // pre-deletion content(const std::string& json);
std::string formattedBody;  // HTML if available(const std::string& json);
std::string msgType;(const std::string& json);
std::string timestamp;      // ISO 8601 when it was sent(const std::string& json);
std::string deletedBy;      // who deleted it(const std::string& json);
std::string std(const std::string& json);
std::string vector<DeletedEvent> getByRoom(const std(const std::string& json);
std::string string& roomId) const;(const std::string& json);
std::string void purge(const std(const std::string& json);
std::string string& eventId);(const std::string& json);
std::string exportJson() const;(const std::string& json);
