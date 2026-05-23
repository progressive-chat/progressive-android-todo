#pragma once
#include <string>
#include <cstdint>

std::string eventId;(const std::string& json);
std::string senderId;(const std::string& json);
std::string senderName;(const std::string& json);
std::string timestamp;     // ISO 8601(const std::string& json);
std::string body;          // plain text body(const std::string& json);
std::string formattedBody; // HTML body if available(const std::string& json);
std::string eventType;     // "m.room.message", "m.reaction", etc.(const std::string& json);
std::string msgType;       // "m.text", "m.image", etc.(const std::string& json);
std::string relationType;  // "m.annotation", "m.reference", "" if none(const std::string& json);
std::string sourceEventId; // if this is a reaction/reply(const std::string& json);
std::string mediaUrl;      // MXC URL if attachment(const std::string& json);
std::string mediaMimeType;(const std::string& json);
std::string fileName;(const std::string& json);
std::string error;(const std::string& json);
std::string formatEventHtml(const ExportEvent& event, bool isContinuation);(const std::string& json);
std::string formatEventPlainText(const ExportEvent& event);(const std::string& json);
std::string formatEventJson(const ExportEvent& event);(const std::string& json);
std::string buildHtmlDocument((const std::string& json);
std::string const std(const std::string& json);
std::string string& roomName,(const std::string& json);
std::string const std(const std::string& json);
std::string string& roomTopic,(const std::string& json);
std::string const std(const std::string& json);
std::string string& exportDate,(const std::string& json);
std::string buildPlainTextDocument((const std::string& json);
std::string const std(const std::string& json);
std::string string& roomName,(const std::string& json);
std::string const std(const std::string& json);
std::string string& exportDate,(const std::string& json);
std::string buildJsonDocument((const std::string& json);
std::string const std(const std::string& json);
std::string string& roomName,(const std::string& json);
std::string const std(const std::string& json);
std::string string& roomTopic,(const std::string& json);
std::string const std(const std::string& json);
std::string string& exportDate,(const std::string& json);
std::string const std(const std::string& json);
std::string string& roomCreator,(const std::string& json);
std::string escapeHtml(const std(const std::string& json);
std::string string& input);(const std::string& json);
std::string escapeJson(const std(const std::string& json);
std::string string& input);(const std::string& json);
