#pragma once
#include <string>
#include <cstdint>

std::string mxcUrl;              // mxc(const std::string& json);
std::string //server/media_id(const std::string& json);
std::string downloadUrl;         // Resolved HTTP download URL(const std::string& json);
std::string thumbnailUrl;        // Resolved HTTP thumbnail URL(const std::string& json);
std::string mimeType;            // "image/jpeg", "video/mp4", etc.(const std::string& json);
std::string fileName;            // Original file name(const std::string& json);
std::string body;                // Message body text(const std::string& json);
std::string method = "scale";    // "scale" or "crop"(const std::string& json);
std::string resolveMxcDownloadUrl(const std(const std::string& json);
std::string string& mxcUrl, const std(const std::string& json);
std::string string& homeServer);(const std::string& json);
std::string resolveMxcThumbnailUrl(const std(const std::string& json);
std::string string& mxcUrl, const std(const std::string& json);
std::string string& homeServer,(const std::string& json);
std::string extractMxcServerName(const std(const std::string& json);
std::string string& mxcUrl);(const std::string& json);
std::string extractMxcMediaId(const std(const std::string& json);
std::string string& mxcUrl);(const std::string& json);
std::string buildMxcUrl(const std(const std::string& json);
std::string string& serverName, const std(const std::string& json);
std::string string& mediaId);(const std::string& json);
std::string MediaType detectMediaType(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string bool isMimeTypeImage(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string bool isMimeTypeVideo(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string bool isMimeTypeAudio(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string MediaInfo parseMediaInfo(const std(const std::string& json);
std::string string& contentJson);(const std::string& json);
std::string getMediaTypeName(MediaType type);(const std::string& json);
std::string getMediaTypeNameFromMime(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string formatMediaSize(int64_t bytes);(const std::string& json);
std::string formatMediaSizeDouble(double bytes);(const std::string& json);
std::string formatMediaDuration(int durationMs);(const std::string& json);
std::string buildThumbnailCacheKey(const std(const std::string& json);
std::string string& mxcUrl, const ThumbnailConfig& config);(const std::string& json);
std::string bool canGenerateThumbnail(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
