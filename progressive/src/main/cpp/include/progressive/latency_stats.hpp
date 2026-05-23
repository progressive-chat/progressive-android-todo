#pragma once
#include <string>
#include <cstdint>

std::string serverName;    // which homeserver(const std::string& json);
std::string endpoint;      // which API endpoint(const std::string& json);
std::string void record(double latencyMs, const std(const std::string& json);
std::string string& serverName, const std(const std::string& json);
std::string string& endpoint, bool success = true);(const std::string& json);
std::string LatencyStats computeServerStats(const std(const std::string& json);
std::string string& serverName) const;(const std::string& json);
std::string static statsToText(const LatencyStats& stats);(const std::string& json);
std::string static statsToJson(const LatencyStats& stats);(const std::string& json);
std::string static formatLatency(double ms);(const std::string& json);
