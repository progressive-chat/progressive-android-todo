#pragma once
#include <string>
#include <cstdint>

std::string eventId;(const std::string& json);
std::string senderName;(const std::string& json);
std::string senderId;(const std::string& json);
std::string body;               // text to display(const std::string& json);
std::string formattedBody;      // HTML if available(const std::string& json);
std::string timestamp;          // formatted time(const std::string& json);
std::string thumbnailUrl;       // for images/video(const std::string& json);
std::string mxcUrl;(const std::string& json);
std::string previousSenderId;(const std::string& json);
std::string DisplayEventType classifyEvent(const std(const std::string& json);
std::string string& eventType, const std(const std::string& json);
std::string string& msgType);(const std::string& json);
std::string bool isContinuation(const std(const std::string& json);
std::string string& currentSender, const std(const std::string& json);
std::string string& previousSender,(const std::string& json);
std::string bool shouldShowTimestamp(const std(const std::string& json);
std::string string& currentSender, int64_t currentTs,(const std::string& json);
std::string bool shouldShowAvatar(const std(const std::string& json);
std::string string& currentSender, const std(const std::string& json);
std::string string& previousSender,(const std::string& json);
std::string getEventTypeDescription(DisplayEventType type);(const std::string& json);
std::string getEventTypeIcon(DisplayEventType type);(const std::string& json);
std::string formatEventPreview(const DisplayEvent& event, bool showSender);(const std::string& json);
std::string formatMemberEvent(const std(const std::string& json);
std::string string& senderName, const std(const std::string& json);
std::string string& membership,(const std::string& json);
std::string const std(const std::string& json);
std::string string& targetName, const std(const std::string& json);
std::string string& reason = "");(const std::string& json);
