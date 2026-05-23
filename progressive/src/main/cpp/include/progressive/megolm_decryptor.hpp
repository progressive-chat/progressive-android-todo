#pragma once
#include <string>
#include <cstdint>

std::string sessionId;        // Unique session identifier(const std::string& json);
std::string senderKey;        // Curve25519 key of sender(const std::string& json);
std::string bool parseMegolmSessionKey(const std(const std::string& json);
std::string string& keyBase64, std(const std::string& json);
std::string vector<uint8_t>& sessionKey);(const std::string& json);
std::string megolmDecrypt(MegolmSession& session, const std(const std::string& json);
std::string string& ciphertext);(const std::string& json);
std::string getMegolmSessionId(const MegolmSession& session);(const std::string& json);
std::string exportMegolmSession(const MegolmSession& session);(const std::string& json);
std::string bool addSession(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& senderKey,(const std::string& json);
std::string const std(const std::string& json);
std::string string& sessionId, const std(const std::string& json);
std::string string& sessionKeyBase64);(const std::string& json);
std::string MegolmSession* findSession(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& senderKey,(const std::string& json);
std::string const std(const std::string& json);
std::string string& sessionId);(const std::string& json);
std::string void clearRoom(const std(const std::string& json);
std::string string& roomId);(const std::string& json);
std::string roomId;(const std::string& json);
std::string senderKey;(const std::string& json);
std::string sessionId;(const std::string& json);
std::string return std(const std::string& json);
std::string hash<std(const std::string& json);
std::string string>()(k.roomId + k.senderKey + k.sessionId);(const std::string& json);
