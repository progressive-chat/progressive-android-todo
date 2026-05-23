#pragma once
#include <string>
#include <cstdint>

std::string name;              // "m.megolm.v1.aes-sha2", "m.olm.v1.curve25519-aes-sha2"(const std::string& json);
std::string keySize;           // "256"(const std::string& json);
std::string cipher;            // "aes-sha2"(const std::string& json);
std::string algorithm;(const std::string& json);
std::string senderKey;(const std::string& json);
std::string deviceId;(const std::string& json);
std::string sessionId;(const std::string& json);
std::string ciphertext;(const std::string& json);
std::string senderKey;(const std::string& json);
std::string deviceId;(const std::string& json);
std::string sessionId;(const std::string& json);
std::string EncryptionAlgorithm parseEncryptionAlgorithm(const std(const std::string& json);
std::string string& algorithmStr);(const std::string& json);
std::string EncryptedEventHeader parseEncryptedHeader(const std(const std::string& json);
std::string string& contentJson);(const std::string& json);
std::string extractSenderKey(const std(const std::string& json);
std::string string& contentJson);(const std::string& json);
std::string extractSessionId(const std(const std::string& json);
std::string string& contentJson);(const std::string& json);
std::string bool isSecureAlgorithm(const std(const std::string& json);
std::string string& algorithm);(const std::string& json);
std::string formatEncryptionInfo(const EncryptedEventHeader& header);(const std::string& json);
std::string sessionId;(const std::string& json);
std::string senderKey;(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& sessionIds,(const std::string& json);
std::string const std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string>& senderKeys,(const std::string& json);
std::string formatSessionUsage(const SessionUsage& session);(const std::string& json);
