#pragma once
#include <string>
#include <cstdint>

std::string input;       // original input(const std::string& json);
std::string resolved;    // resolved MXID or room ID(const std::string& json);
std::string type;        // "user", "room", "alias", "event", "unknown"(const std::string& json);
std::string ResolvedId resolveMatrixId(const std(const std::string& json);
std::string string& input);(const std::string& json);
std::string medium;     // "email", "msisdn"(const std::string& json);
std::string address;    // "user@example.com", "+1234567890"(const std::string& json);
std::string IdentityThreePid parseThreePid(const std(const std::string& json);
std::string string& input);(const std::string& json);
std::string bool isEmail(const std(const std::string& json);
std::string string& input);(const std::string& json);
std::string bool isMsisdn(const std(const std::string& json);
std::string string& input);(const std::string& json);
std::string formatThreePid(const IdentityThreePid& pid);(const std::string& json);
std::string bool isAmbiguousName(const std(const std::string& json);
std::string string& name1, const std(const std::string& json);
std::string string& name2);(const std::string& json);
std::string disambiguateName(const std(const std::string& json);
std::string string& displayName, const std(const std::string& json);
std::string string& mxid);(const std::string& json);
std::string bool isValidDisplayName(const std(const std::string& json);
std::string string& name);(const std::string& json);
std::string getIdentityInitials(const std(const std::string& json);
std::string string& displayName, int maxChars = 2);(const std::string& json);
std::string bool isCanonicalAlias(const std(const std::string& json);
std::string string& alias, const std(const std::string& json);
std::string string& expectedRoomId);(const std::string& json);
std::string extractAliasLocalpart(const std(const std::string& json);
std::string string& alias);(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> suggestAliases(const std(const std::string& json);
std::string string& roomName, int maxResults = 3);(const std::string& json);
