#pragma once
#include <string>
#include <cstdint>

std::string senderName;(const std::string& json);
std::string body;          // message text(const std::string& json);
std::string timestamp;     // short time like "12(const std::string& json);
std::string 34"(const std::string& json);
std::string attachmentType; // "image", "video", "file", "audio"(const std::string& json);
std::string senderId;      // for dedup(const std::string& json);
std::string lastMessage;    // single-line preview (current behavior)(const std::string& json);
std::string lastSender;(const std::string& json);
std::string lastTimestamp;(const std::string& json);
std::string draftText;(const std::string& json);
std::string toJson() const;(const std::string& json);
std::string truncateMessage(const std(const std::string& json);
std::string string& body, int maxLen = 60);(const std::string& json);
std::string formatShortTime(int64_t epochMs);(const std::string& json);
std::string PreviewIconType getPreviewIcon(const std(const std::string& json);
std::string string& attachmentType);(const std::string& json);
std::string text;(const std::string& json);
std::string color; // hex color or empty for default(const std::string& json);
std::string formatChatPreviewWithConfig(const ChatPreviewState& state, const ChatPreviewConfig& config);(const std::string& json);
std::string formatTypingPreview(const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& typingUserNames);(const std::string& json);
std::string formatDraftPreview(const std(const std::string& json);
std::string string& draftText, int maxLen = 40);(const std::string& json);
std::string formatFailedPreview(const std(const std::string& json);
std::string string& originalBody, int maxLen = 40);(const std::string& json);
std::string formatPreviewLinesJson(const std(const std::string& json);
std::string vector<ChatPreviewLine>& lines);(const std::string& json);
