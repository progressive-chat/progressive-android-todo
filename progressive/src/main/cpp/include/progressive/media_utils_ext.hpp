#pragma once
#include <string>
#include <cstdint>

namespace progressive {

struct MediaInfo {
    std::string mxcUrl;
    std::string mimeType;
    std::string thumbnailUrl;
    int width = 0;
    int height = 0;
    int64_t sizeBytes = 0;
    int durationMs = 0;
};

// Build media download URL from MXC
std::string buildDownloadUrl(const std::string& mxcUrl, const std::string& homeserver);

// Build thumbnail URL with dimensions
std::string buildThumbnailUrl(const std::string& mxcUrl, const std::string& homeserver,
                                int w, int h, const std::string& method = "crop");

// Check if MIME type requires thumbnail
bool needsThumbnail(const std::string& mimeType, int maxSize = 1024);

// Get max thumbnail dimensions based on screen size hint
std::pair<int,int> getThumbnailDimensions(int screenWidth, int screenHeight, bool isPortrait = true);

// Validate MXC URL format
bool isValidMxcUrl(const std::string& url);

// Extract server from MXC: "mxc://server/mediaId" → "server"
std::string extractMxcServer(const std::string& mxcUrl);
std::string extractMxcMediaId(const std::string& mxcUrl);

// Format media attribution text
std::string formatMediaAttribution(const std::string& author, const std::string& license);

} // namespace progressive
