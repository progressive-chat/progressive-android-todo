#pragma once
#include <string>
#include <cstdint>

std::string inline keyUsageToString(KeyUsage u) {(const std::string& json);
std::string masterKeyId;        // base64-encoded public key(const std::string& json);
std::string warningMessage;     // "This will invalidate all verified devices"(const std::string& json);
std::string CrossSigningStatus parseCrossSigningStatus(const std(const std::string& json);
std::string string& accountDataJson, const std(const std::string& json);
std::string string& userId);(const std::string& json);
std::string formatCrossSigningStatus(const CrossSigningStatus& status);(const std::string& json);
std::string getCrossSigningStorageKey(CrossSigningKey keyType, const std(const std::string& json);
std::string string& userId);(const std::string& json);
std::string parseCrossSigningKeyId(const std(const std::string& json);
std::string string& keyContentJson);(const std::string& json);
std::string bool isKeySignedByMaster(const std(const std::string& json);
std::string string& keyJson, const std(const std::string& json);
std::string string& masterKeyId);(const std::string& json);
std::string buildBootstrapBody(const std(const std::string& json);
std::string string& masterKey, const std(const std::string& json);
std::string string& selfSigningKey,(const std::string& json);
std::string const std(const std::string& json);
std::string string& userSigningKey, const std(const std::string& json);
std::string string& masterKeySignature,(const std::string& json);
std::string const std(const std::string& json);
std::string string& selfSigningSignature, const std(const std::string& json);
std::string string& userSigningSignature);(const std::string& json);
