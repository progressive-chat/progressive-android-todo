#pragma once
#include <string>
#include <cstdint>

std::string localId;          // local event ID (txnId)(const std::string& json);
std::string roomId;(const std::string& json);
std::string body;             // message content(const std::string& json);
std::string msgType;          // "m.text", "m.image", "m.file", etc.(const std::string& json);
std::string error;            // last error message(const std::string& json);
std::string reason;           // why this decision was made(const std::string& json);
std::string RetryDecision decideRetry(const PendingMessage& msg, int errorCode, const std(const std::string& json);
std::string string& retryAfterHeader = "");(const std::string& json);
std::string PendingMessage afterAttempt(PendingMessage msg, bool success, int errorCode, const std(const std::string& json);
std::string string& error, int64_t nowMs);(const std::string& json);
std::string pendingMessageToJson(const PendingMessage& msg);(const std::string& json);
std::string queueToJson(const std(const std::string& json);
std::string vector<PendingMessage>& queue);(const std::string& json);
std::string formatMessageStatus(MessageSendState state);(const std::string& json);
std::string formatRetryBadge(int retryCount);(const std::string& json);
std::string error;(const std::string& json);
std::string PendingMessage editPendingMessage(std(const std::string& json);
std::string vector<PendingMessage>& queue, const std(const std::string& json);
std::string string& localId, const std(const std::string& json);
std::string string& newBody, int64_t nowMs);(const std::string& json);
