#pragma once
#include <string>
#include <cstdint>

std::string allowedExtensions;             // "jpg,png,gif,mp4" (comma-separated)(const std::string& json);
std::string fileName;(const std::string& json);
std::string mimeType;(const std::string& json);
std::string extension;(const std::string& json);
std::string errorMessage;(const std::string& json);
std::string FileValidation validateFile(const std(const std::string& json);
std::string string& fileName, const std(const std::string& json);
std::string string& mimeType,(const std::string& json);
std::string getFileExtension(const std(const std::string& json);
std::string string& fileName);(const std::string& json);
std::string getMimeFromExtension(const std(const std::string& json);
std::string string& extension);(const std::string& json);
std::string bool isImageMime(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string bool isVideoMime(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string bool isAudioMime(const std(const std::string& json);
std::string string& mimeType);(const std::string& json);
std::string formatFileSize(int64_t bytes);(const std::string& json);
std::string bool isExtensionAllowed(const std(const std::string& json);
std::string string& extension, const std(const std::string& json);
std::string string& allowedList);(const std::string& json);
std::string getFileTypeCategory(const std(const std::string& json);
std::string string& mimeType, const std(const std::string& json);
std::string string& extension);(const std::string& json);
std::string sanitizeFileName(const std(const std::string& json);
std::string string& fileName);(const std::string& json);
