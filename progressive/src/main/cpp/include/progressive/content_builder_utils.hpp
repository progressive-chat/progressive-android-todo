#pragma once
#include <string>

namespace progressive {

// Build text message content
std::string buildTextContent(const std::string& body, const std::string& formattedBody = "");

// Build notice message content
std::string buildNoticeContent(const std::string& body);

// Build emote message content
std::string buildEmoteContent(const std::string& body);

// Build image message content
std::string buildImageContent(const std::string& mxcUrl, const std::string& body,
                                int w, int h, int64_t size, const std::string& mime = "image/jpeg");

// Build video message content
std::string buildVideoContent(const std::string& mxcUrl, const std::string& body,
                                int w, int h, int durationMs, const std::string& mime = "video/mp4");

// Build sticker message content
std::string buildStickerContent(const std::string& mxcUrl, const std::string& body);

// Build topic change event
std::string buildTopicChangeContent(const std::string& topic);

// Build room name change event
std::string buildRoomNameChangeContent(const std::string& name);

// Generic content builder with arbitrary fields
std::string buildContentJson(const std::string& msgType, const std::string& body,
                              const std::string& extraFields = "");

} // namespace progressive
