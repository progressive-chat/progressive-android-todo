#pragma once
#include <string>
#include <cstdint>

std::string parseTurnServers(const std::string& json);
std::string buildIceCandidateJson(const std::string& json);
std::string formatSdpOffer(const std::string& json);
std::string parseSdpAnswer(const std::string& json);
std::string extractFingerprint(const std::string& json);
