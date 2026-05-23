#pragma once
#include <string>
#include <cstdint>

std::string userId;(const std::string& json);
std::string accessToken;(const std::string& json);
std::string refreshToken;(const std::string& json);
std::string homeServerUrl;(const std::string& json);
std::string deviceId;(const std::string& json);
std::string deviceName;(const std::string& json);
std::string displayName;(const std::string& json);
std::string avatarUrl;(const std::string& json);
std::string encryptAccountData(const AccountData& data, const std(const std::string& json);
std::string string& passphrase);(const std::string& json);
std::string AccountData decryptAccountData(const std(const std::string& json);
std::string string& encrypted, const std(const std::string& json);
std::string string& passphrase);(const std::string& json);
std::string accountToJson(const AccountData& data);(const std::string& json);
std::string AccountData jsonToAccount(const std::string& json);
std::string // base64Encode(const std(const std::string& json);
std::string string& input);(const std::string& json);
std::string // base64Decode(const std(const std::string& json);
std::string string& input);(const std::string& json);
