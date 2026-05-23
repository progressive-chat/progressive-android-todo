#pragma once
#include <string>
#include <cstdint>

std::string eventId;       // extracted event ID(const std::string& json);
std::string originalText;  // the link text (e.g. "$abc123" or full URL)(const std::string& json);
std::string resolvedBody;  // the resolved message body(const std::string& json);
std::string resolvedSender;// who sent the resolved message(const std::string& json);
std::string std(const std::string& json);
std::string vector<EventLink> extractEventLinks(const std(const std::string& json);
std::string string& body);(const std::string& json);
std::string // bool isEventId(const std(const std::string& json);
std::string string& text);  // now in matrix_patterns.hpp(const std::string& json);
std::string struct MatrixToLink { eventId; std(const std::string& json);
std::string string roomId; };(const std::string& json);
std::string MatrixToLink parseMatrixToUrl(const std(const std::string& json);
std::string string& url);(const std::string& json);
std::string formatResolvedEventText(const std(const std::string& json);
std::string string& senderName, const std(const std::string& json);
std::string string& body);(const std::string& json);
std::string bool isExpandedText(const std(const std::string& json);
std::string string& text);(const std::string& json);
std::string formatTimestamp(int64_t epochMs, bool includeSeconds);(const std::string& json);
std::string formatFullTimestamp(int64_t epochMs);(const std::string& json);
