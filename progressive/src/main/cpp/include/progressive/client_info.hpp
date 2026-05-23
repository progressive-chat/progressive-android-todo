#pragma once
#include <string>
#include <cstdint>

std::string appName;           // "Progressive Chat"(const std::string& json);
std::string appVersion;        // "1.0.0"(const std::string& json);
std::string sdkVersion;        // Matrix SDK version(const std::string& json);
std::string olmVersion;        // libolm version(const std::string& json);
std::string platform;          // "Android 14"(const std::string& json);
std::string deviceModel;       // "Pixel 8"(const std::string& json);
std::string architecture;      // "arm64-v8a"(const std::string& json);
std::string gitHash;           // commit SHA(const std::string& json);
std::string buildUserAgent(const ClientVersionInfo& info);(const std::string& json);
std::string buildClientVersionQuery(const ClientVersionInfo& info);(const std::string& json);
std::string parseServerVersion(const std(const std::string& json);
std::string string& apiResponseJson);(const std::string& json);
std::string bool isServerCompatible(const std(const std::string& json);
std::string string& serverVersion, const std(const std::string& json);
std::string string& minRequiredVersion);(const std::string& json);
std::string formatVersionInfo(const ClientVersionInfo& info);(const std::string& json);
std::string int compareSemver(const std(const std::string& json);
std::string string& a, const std(const std::string& json);
std::string string& b);(const std::string& json);
std::string bool satisfiesMinVersion(const std(const std::string& json);
std::string string& current, const std(const std::string& json);
std::string string& minimum);(const std::string& json);
std::string flavor;            // "gplay" or "fdroid"(const std::string& json);
std::string buildType;         // "debug" or "release"(const std::string& json);
std::string applicationId;     // "im.vector.app"(const std::string& json);
std::string versionName;       // "1.0.0"(const std::string& json);
std::string formatBuildInfo(const BuildInfo& info);(const std::string& json);
std::string getAppDisplayName(const BuildInfo& info);(const std::string& json);
