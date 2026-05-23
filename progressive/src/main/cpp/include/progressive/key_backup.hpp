#pragma once
#include <string>
#include <cstdint>

std::string raw;                    // base58-encoded key without spaces(const std::string& json);
std::string formatRecoveryKey(const std(const std::string& json);
std::string string& raw);(const std::string& json);
std::string unformatRecoveryKey(const std(const std::string& json);
std::string string& formatted);(const std::string& json);
std::string RecoveryKey validateRecoveryKey(const std(const std::string& json);
std::string string& key);(const std::string& json);
std::string extractCurveKeyFromRecoveryKey(const std(const std::string& json);
std::string string& recoveryKey);(const std::string& json);
std::string computeRecoveryKey(const std(const std::string& json);
std::string string& curve25519Key);(const std::string& json);
std::string bool validateRecoveryKeyChecksum(const std(const std::string& json);
std::string string& rawKey);(const std::string& json);
std::string version;          // backup version identifier(const std::string& json);
std::string algorithm;        // "m.megolm_backup.v1.curve25519-aes-sha2"(const std::string& json);
std::string authData;         // signed JSON with public key and signatures(const std::string& json);
std::string error;(const std::string& json);
std::string KeyBackupVersion parseKeyBackupVersion(const std::string& json);
std::string bool isSupportedBackupAlgorithm(const std(const std::string& json);
std::string string& algorithm);(const std::string& json);
std::string keyBackupVersionToJson(const KeyBackupVersion& backup);(const std::string& json);
std::string getBackupAlgorithmDescription(const std(const std::string& json);
std::string string& algorithm);(const std::string& json);
std::string getRecoveryKeyExample();(const std::string& json);
std::string bool isValidPassphrase(const std(const std::string& json);
std::string string& passphrase);(const std::string& json);
std::string algorithm;(const std::string& json);
std::string salt;(const std::string& json);
std::string keyId;(const std::string& json);
std::string algorithm;(const std::string& json);
std::string name;(const std::string& json);
std::string publicKey;(const std::string& json);
std::string SecretStorageKey parseSecretStorageKey(const std(const std::string& json);
std::string string& keyId, const std(const std::string& json);
std::string string& json);(const std::string& json);
std::string secretStorageKeyToJson(const SecretStorageKey& key);(const std::string& json);
