#pragma once
#include <string>
#include <cstdint>

std::string url;(const std::string& json);
std::string data;(const std::string& json);
std::string data;              // The fetched/cached content(const std::string& json);
std::string errorMessage;      // Error message if request failed(const std::string& json);
std::string rawCacheEntryToJson(const RawCacheEntry& entry);(const std::string& json);
std::string RawCacheEntry rawCacheEntryFromJson(const std::string& json);
std::string cacheKeyForUrl(const std(const std::string& json);
std::string string& url);(const std::string& json);
