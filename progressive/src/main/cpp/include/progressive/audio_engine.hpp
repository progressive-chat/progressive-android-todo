#pragma once
#include <string>
#include <cstdint>

std::string url;          // MXC or HTTP URL(const std::string& json);
std::string title;        // track title (sender name or filename)(const std::string& json);
std::string roomId;       // which room it came from(const std::string& json);
std::string eventId;      // which event(const std::string& json);
std::string formatDuration(int64_t ms);(const std::string& json);
std::string formatPositionInfo(int64_t positionMs, int64_t durationMs);(const std::string& json);
std::string bool isSupportedAudioType(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string mimeToExtension(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
