#pragma once
#include <string>
#include <cstdint>

std::string fileName;(const std::string& json);
std::string mimeType;(const std::string& json);
std::string mxcUri;            // upload target(const std::string& json);
std::string contentUrl;        // final mxc(const std::string& json);
std::string // URI(const std::string& json);
std::string thumbnailUrl;      // mxc(const std::string& json);
std::string // for thumbnail(const std::string& json);
std::string mimeType;(const std::string& json);
std::string fileName;(const std::string& json);
std::string mxcUri;(const std::string& json);
std::string mimeType;(const std::string& json);
std::string fileName;(const std::string& json);
std::string cachePath;         // local file path(const std::string& json);
std::string buildMediaUploadBody(const MediaUploadConfig& config);(const std::string& json);
std::string parseUploadResponse(const std(const std::string& json);
std::string string& responseJson);(const std::string& json);
std::string MediaDownloadInfo parseMediaDownloadInfo(const std(const std::string& json);
std::string string& mxcUri, const std(const std::string& json);
std::string string& responseJson);(const std::string& json);
std::string buildThumbnailDimensions(const MediaUploadConfig& config);(const std::string& json);
std::string formatUploadProgress(int64_t uploaded, int64_t total);(const std::string& json);
std::string bool shouldGenerateThumbnail(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string getMatrixContentType(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string mimeToMsgType(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string hash;(const std::string& json);
std::string bool isValidBlurhash(const std(const std::string& json);
std::string string& hash);(const std::string& json);
std::string BlurhashResult parseBlurhash(const std(const std::string& json);
std::string string& contentJson);(const std::string& json);
