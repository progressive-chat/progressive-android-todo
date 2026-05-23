#pragma once
#include <string>
#include <cstdint>

std::string mxcUri;(const std::string& json);
std::string serverName;      // which scanner server(const std::string& json);
std::string threat;          // detected threat name(const std::string& json);
std::string recommendation;  // "allow", "block", "warn"(const std::string& json);
std::string ScanResult parseScanResult(const std(const std::string& json);
std::string string& apiResponseJson);(const std::string& json);
std::string buildScanRequestBody(const std(const std::string& json);
std::string string& mxcUri);(const std::string& json);
std::string bool isContentScannerAvailable(const std(const std::string& json);
std::string string& serverCapabilitiesJson);(const std::string& json);
std::string formatScanResult(const ScanResult& result);(const std::string& json);
std::string eventId;(const std::string& json);
std::string body;(const std::string& json);
std::string adminContact;(const std::string& json);
std::string noticeType;      // "m.server_notice"(const std::string& json);
std::string ServerNoticeEvent parseServerNoticeEvent(const std(const std::string& json);
std::string string& eventContentJson, const std(const std::string& json);
std::string string& eventId);(const std::string& json);
std::string bool isServerNotice(const std(const std::string& json);
std::string string& eventContentJson);(const std::string& json);
std::string formatServerNoticeEvent(const ServerNoticeEvent& notice);(const std::string& json);
std::string version;(const std::string& json);
std::string url;(const std::string& json);
std::string TosInfo parseTosInfo(const std(const std::string& json);
std::string string& responseJson);(const std::string& json);
std::string bool mustAcceptTos(const std(const std::string& json);
std::string string& responseJson);(const std::string& json);
std::string buildTosAcceptBody(const std(const std::string& json);
std::string string& version);(const std::string& json);
