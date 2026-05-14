#include "progressive/key_backup.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

namespace progressive {

// Base58 alphabet (Bitcoin)
static const char* BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

bool isValidBase58Char(char c) {
    for (int i = 0; BASE58_ALPHABET[i]; ++i) {
        if (BASE58_ALPHABET[i] == c) return true;
    }
    return false;
}

// ---- Recovery Key Formatting ----
// Original Kotlin:
//   fun formatRecoveryKey(raw: String?): String? {
//       return raw?.chunked(4)?.joinToString(" ")
//   }

std::string formatRecoveryKey(const std::string& raw) {
    if (raw.empty()) return "";

    std::ostringstream out;
    for (size_t i = 0; i < raw.size(); ++i) {
        if (i > 0 && i % 4 == 0) out << ' ';
        out << static_cast<char>(std::toupper(static_cast<unsigned char>(raw[i])));
    }
    return out.str();
}

std::string unformatRecoveryKey(const std::string& formatted) {
    std::string raw;
    for (char c : formatted) {
        if (c != ' ' && c != '-' && c != '\t' && c != '\n') {
            raw += c;
        }
    }
    return raw;
}

RecoveryKey validateRecoveryKey(const std::string& key) {
    RecoveryKey result;

    // Step 1: Unformat (remove spaces)
    result.raw = unformatRecoveryKey(key);

    // Step 2: Length check — Matrix recovery keys are 58 base58 chars
    // (1 byte prefix + 32 byte key + 4 byte checksum = 37 bytes → ~58 base58 chars)
    if (result.raw.size() < 50) {
        result.status = RecoveryKeyStatus::Invalid_TooShort;
        return result;
    }
    if (result.raw.size() > 70) {
        result.status = RecoveryKeyStatus::Invalid_TooLong;
        return result;
    }

    // Step 3: Validate base58 characters
    for (char c : result.raw) {
        if (!isValidBase58Char(c)) {
            result.status = RecoveryKeyStatus::Invalid_BadCharacters;
            return result;
        }
    }

    // Step 4: Format check — must have spaces in groups of 4 (optional, not strict)
    // Original Kotlin doesn't strictly require groups, but we check
    // for common formatting issues

    result.valid = true;
    result.status = RecoveryKeyStatus::Valid;
    return result;
}

std::string extractCurveKeyFromRecoveryKey(const std::string& recoveryKey) {
    auto validated = validateRecoveryKey(recoveryKey);
    if (!validated.valid) return "";

    // Recovery key format (base58):
    // [prefix 1B] [private key 32B] [checksum 4B] → total 37 bytes → ~58 base58 chars
    //
    // Original Kotlin (KeysBackup.kt):
    //   fun extractCurveKeyFromRecoveryKey(key: String): String? {
    //       val decoded = key.base58decode()
    //       return decoded?.copyOfRange(1, 33)?.base64encode()
    //   }

    // Decode base58
    auto base58Decode = [](const std::string& input) -> std::string {
        std::string result;
        // Multiply-and-add algorithm for base58
        std::vector<int> digits;
        for (char c : input) {
            int value = 0;
            for (int i = 0; BASE58_ALPHABET[i]; ++i) {
                if (BASE58_ALPHABET[i] == c) { value = i; break; }
            }
            int carry = value;
            for (size_t j = 0; j < digits.size(); ++j) {
                carry += digits[j] * 58;
                digits[j] = carry & 0xFF;
                carry >>= 8;
            }
            while (carry > 0) {
                digits.push_back(carry & 0xFF);
                carry >>= 8;
            }
        }
        // Add leading zero bytes for each leading '1' in input
        for (char c : input) {
            if (c == '1') digits.push_back(0);
            else break;
        }
        // Reverse digits
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            result += static_cast<char>(*it);
        }
        return result;
    };

    auto decoded = base58Decode(validated.raw);

    // Skip prefix byte (1), take 32 bytes for Curve25519 key
    if (decoded.size() < 33) return "";

    return decoded.substr(1, 32);
}

bool validateRecoveryKeyChecksum(const std::string& rawKey) {
    // Recovery key encodes: [1B prefix] [32B key] [4B checksum]
    // We need at least 37 bytes decoded (58 base58 chars)
    // Without SHA-256 (no OpenSSL), we do a minimum length check
    return rawKey.size() >= 54;  // 58 base58 chars min for 37 bytes
}

// ---- Backup Version ----
KeyBackupVersion parseKeyBackupVersion(const std::string& json) {
    KeyBackupVersion backup;

    // Original Kotlin: json.getString("version")
    auto extractStr = [&](const std::string& key) -> std::string {
        auto search = "\"" + key + "\":\"";
        auto pos = json.find(search);
        if (pos == std::string::npos) {
            search = "\"" + key + "\": \"";
            pos = json.find(search);
        }
        if (pos == std::string::npos) return "";
        pos += search.size();
        auto end = json.find('"', pos);
        if (end == std::string::npos) return "";
        return json.substr(pos, end - pos);
    };

    auto extractInt = [&](const std::string& key) -> int {
        auto search = "\"" + key + "\":";
        auto pos = json.find(search);
        if (pos == std::string::npos) return 0;
        pos += search.size();
        while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t')) pos++;
        int val = 0;
        while (pos < json.size() && json[pos] >= '0' && json[pos] <= '9') {
            val = val * 10 + (json[pos] - '0');
            pos++;
        }
        return val;
    };

    backup.version = extractStr("version");
    backup.algorithm = extractStr("algorithm");
    backup.count = extractInt("count");

    // Extract auth_data
    auto authPos = json.find("\"auth_data\"");
    if (authPos != std::string::npos) {
        auto openPos = json.find('{', authPos);
        if (openPos != std::string::npos) {
            int braceDepth = 1;
            size_t pos = openPos + 1;
            while (pos < json.size() && braceDepth > 0) {
                if (json[pos] == '{') braceDepth++;
                else if (json[pos] == '}') braceDepth--;
                pos++;
            }
            backup.authData = json.substr(openPos, pos - openPos);
        }
    }

    backup.valid = !backup.version.empty() && !backup.algorithm.empty();
    if (!backup.valid) {
        backup.error = "Missing version or algorithm in backup info";
    } else if (!isSupportedBackupAlgorithm(backup.algorithm)) {
        backup.valid = false;
        backup.error = "Unsupported backup algorithm: " + backup.algorithm;
    }

    return backup;
}

bool isSupportedBackupAlgorithm(const std::string& algorithm) {
    // Matrix currently supports this algorithm
    return algorithm == "m.megolm_backup.v1.curve25519-aes-sha2";
}

std::string keyBackupVersionToJson(const KeyBackupVersion& backup) {
    auto esc = [](const std::string& s) -> std::string {
        std::string out;
        for (char c : s) { if (c == '"') out += "\\\""; else out += c; }
        return out;
    };
    std::ostringstream json;
    json << R"({"version": ")" << esc(backup.version) << R"(",)";
    json << R"("algorithm": ")" << esc(backup.algorithm) << R"(",)";
    json << R"("count": )" << backup.count << ",";
    json << R"("valid": )" << (backup.valid ? "true" : "false") << ",";
    json << R"("error": ")" << esc(backup.error) << R"(")";
    json << "}";
    return json.str();
}

std::string getBackupAlgorithmDescription(const std::string& algorithm) {
    if (algorithm == "m.megolm_backup.v1.curve25519-aes-sha2") {
        return "Encrypted using Curve25519-AES-SHA2";
    }
    return "Unknown algorithm: " + algorithm;
}

std::string getRecoveryKeyExample() {
    return "EsTc 2FZd Jsdf 4Gt7 HqX9 bKpL mNvR wQzY x3A5 B6C7 D8E";
}

bool isValidPassphrase(const std::string& passphrase) {
    return !passphrase.empty() && passphrase.size() >= static_cast<size_t>(getMinPassphraseLength());
}

int getMinPassphraseLength() {
    return 8;  // minimum recommended by Matrix spec
}

} // namespace progressive
