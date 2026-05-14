#ifndef PROGRESSIVE_KEY_BACKUP_HPP
#define PROGRESSIVE_KEY_BACKUP_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace progressive {

// ---- Key Backup / Recovery Key Formatter ----
// Ported from: org.matrix.android.sdk.internal.crypto.keysbackup.KeysBackup.kt
//              im.vector.app.features.crypto.keysbackup.setup.KeysBackupSetupSharedViewModel.kt
//              org.matrix.android.sdk.internal.crypto.keysbackup.util.extractCurveKeyFromRecoveryKey

// Recovery key status after parsing
enum class RecoveryKeyStatus {
    Valid,
    Invalid_TooShort,
    Invalid_TooLong,
    Invalid_BadCharacters,     // invalid base58 characters
    Invalid_Checksum,          // checksum mismatch
    Invalid_Format,            // wrong format (not space-separated)
};

struct RecoveryKey {
    std::string raw;                    // base58-encoded key without spaces
    bool valid = false;
    RecoveryKeyStatus status = RecoveryKeyStatus::Valid;
};

// ---- Recovery Key Formatting ----
// Original Kotlin (KeysBackupSetupSharedViewModel.kt):
//   fun formatRecoveryKey(raw: String): String {
//       return raw.chunked(4).joinToString(" ")
//   }
// "EsTc2FZdJsdf4Gt7HqX9bKpLmNvRwQzYx3A5B6C7D8E" → "EsTc 2FZd Jsdf 4Gt7 HqX9 bKpL mNvR wQzY x3A5 B6C7 D8E"

// Format a raw recovery key into 4-character groups separated by spaces.
std::string formatRecoveryKey(const std::string& raw);

// Unformat: remove spaces and uppercase to get raw key.
// "EsTc 2FZd Jsdf" → "EsTc2FZdJsdf"
std::string unformatRecoveryKey(const std::string& formatted);

// Validate a recovery key format.
RecoveryKey validateRecoveryKey(const std::string& key);

// Check if a character is valid in base58 (Bitcoin alphabet).
// Base58 chars: 123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz
bool isValidBase58Char(char c);

// Decode a recovery key to extract the Curve25519 private key.
// The recovery key encodes: prefix(1 byte) + private_key(32 bytes) + checksum(4 bytes)
// Encoded in base58.
// Returns empty string if invalid.
std::string extractCurveKeyFromRecoveryKey(const std::string& recoveryKey);

// Validate the checksum of a recovery key.
// The last 4 bytes of the decoded data are a SHA-256 checksum.
// We do a simple length check since actual SHA-256 requires OpenSSL.
bool validateRecoveryKeyChecksum(const std::string& rawKey);

// ---- Backup Version Info ----

struct KeyBackupVersion {
    std::string version;          // backup version identifier
    std::string algorithm;        // "m.megolm_backup.v1.curve25519-aes-sha2"
    std::string authData;         // signed JSON with public key and signatures
    int count = 0;                // number of keys in backup
    bool valid = false;
    std::string error;
};

// Parse key backup version info from JSON (from GET /room_keys/version).
// Original Kotlin (KeysBackup.kt):
//   data class KeysBackupVersion(
//       @Json(name = "version") val version: String,
//       @Json(name = "algorithm") val algorithm: String,
//       @Json(name = "auth_data") val authData: JsonObject,
//       @Json(name = "count") val count: Int
//   )
KeyBackupVersion parseKeyBackupVersion(const std::string& json);

// Check if the backup algorithm is supported.
// Currently supports: m.megolm_backup.v1.curve25519-aes-sha2
bool isSupportedBackupAlgorithm(const std::string& algorithm);

// Format key backup info as JSON for the Kotlin UI.
std::string keyBackupVersionToJson(const KeyBackupVersion& backup);

// Get a human-readable description of the backup algorithm.
std::string getBackupAlgorithmDescription(const std::string& algorithm);

// Generate a recovery key suggestion (for display to user).
// NOT a real key — just a formatted example.
std::string getRecoveryKeyExample();

// Validate a passphrase: must be non-empty, min length recommended.
bool isValidPassphrase(const std::string& passphrase);

// Get the minimum recommended passphrase length.
int getMinPassphraseLength();

} // namespace progressive

#endif // PROGRESSIVE_KEY_BACKUP_HPP
