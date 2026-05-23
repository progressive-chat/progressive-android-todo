#pragma once
#include <string>
#include <cstdint>

std::string code;            // Matrix reason code(const std::string& json);
std::string description;     // human-readable(const std::string& json);
std::string eventId;(const std::string& json);
std::string roomId;(const std::string& json);
std::string reason;           // reason code or custom text(const std::string& json);
std::string buildReportBody(const ReportRequest& request);(const std::string& json);
std::string bool isValidReportReason(const std(const std::string& json);
std::string string& reason);(const std::string& json);
std::string bool isStandardReason(const std(const std::string& json);
std::string string& reason);(const std::string& json);
std::string getReasonDescription(const std(const std::string& json);
std::string string& code);(const std::string& json);
std::string formatReportConfirmation(const ReportRequest& request);(const std::string& json);
std::string description;(const std::string& json);
std::string logs;            // base64-encoded log content(const std::string& json);
std::string version;(const std::string& json);
std::string deviceInfo;(const std::string& json);
std::string userId;(const std::string& json);
std::string buildBugReportBody(const BugReport& report);(const std::string& json);
std::string formatBugReport(const BugReport& report);(const std::string& json);
std::string truncateReportDescription(const std(const std::string& json);
std::string string& desc, int maxLen = 2000);(const std::string& json);
