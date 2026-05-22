#pragma once
#include <string>
#include <cstdint>

namespace progressive {

struct FileUploadInfo {
    std::string mxcUrl;
    std::string mimeType;
    std::string fileName;
    int64_t fileSizeBytes = 0;
    int width = 0;
    int height = 0;
};

// Build file upload event content
std::string buildFileUploadContent(const FileUploadInfo& info, const std::string& body = "");

// Parse file upload info from event
FileUploadInfo parseFileUpload(const std::string& json);

// Format file size for display ("1.2 MB", "340 KB", "2.1 GB")
std::string formatFileSize(int64_t bytes);

// Get file extension from mime type
std::string getFileExtension(const std::string& mimeType);

// Get file icon name from mime type
std::string getFileIcon(const std::string& mimeType);

// Check if file is an image (for thumbnail)
bool isFileImage(const std::string& mimeType);

// Build thumbnail URL
std::string buildThumbnailUrl(const std::string& mxcUrl, const std::string& homeserver,
                                int width, int height, const std::string& method = "scale");

} // namespace progressive
