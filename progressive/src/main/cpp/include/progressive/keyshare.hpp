#pragma once
#include <string>
#include <cstdint>

std::string requestId;(const std::string& json);
std::string roomId;(const std::string& json);
std::string sessionId;(const std::string& json);
std::string senderKey;(const std::string& json);
std::string algorithm;       // "m.megolm.v1.aes-sha2"(const std::string& json);
std::string requestingDeviceId;(const std::string& json);
std::string requestingUserId;(const std::string& json);
std::string sessionKey;      // exported session key(const std::string& json);
std::string errorMessage;(const std::string& json);
std::string KeyRequestInfo parseKeyRequest(const std(const std::string& json);
std::string string& eventContentJson, const std(const std::string& json);
std::string string& eventId,(const std::string& json);
std::string const std(const std::string& json);
std::string string& senderId);(const std::string& json);
std::string bool shouldShareKey(const std(const std::string& json);
std::string string& algorithm, bool hasSession,(const std::string& json);
std::string buildForwardedKeyContent(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& sessionId,(const std::string& json);
std::string const std(const std::string& json);
std::string string& sessionKey, int messageIndex, const std(const std::string& json);
std::string string& algorithm,(const std::string& json);
std::string buildKeyRequestBody(const std(const std::string& json);
std::string string& roomId, const std(const std::string& json);
std::string string& sessionId,(const std::string& json);
std::string const std(const std::string& json);
std::string string& senderKey, const std(const std::string& json);
std::string string& algorithm,(const std::string& json);
std::string const std(const std::string& json);
std::string string& requestId, const std(const std::string& json);
std::string string& requestingDeviceId);(const std::string& json);
std::string buildKeyRequestCancelBody(const std(const std::string& json);
std::string string& requestId);(const std::string& json);
std::string formatKeyRequestNotification(const KeyRequestInfo& info);(const std::string& json);
