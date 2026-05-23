#pragma once
#include <string>
#include <cstdint>

std::string code;              // M_FORBIDDEN, M_UNKNOWN, etc.(const std::string& json);
std::string message;           // human-readable error message(const std::string& json);
std::string std(const std::string& json);
std::string optional<std(const std::string& json);
std::string string> consentUri;       // M_CONSENT_NOT_GIVEN(const std::string& json);
std::string std(const std::string& json);
std::string optional<std(const std::string& json);
std::string string> limitType;        // M_RESOURCE_LIMIT_EXCEEDED(const std::string& json);
std::string std(const std::string& json);
std::string optional<std(const std::string& json);
std::string string> adminUri;         // M_RESOURCE_LIMIT_EXCEEDED(const std::string& json);
std::string std(const std::string& json);
std::string optional<std(const std::string& json);
std::string string> newLookupPepper;  // M_INVALID_PEPPER(const std::string& json);
std::string std(const std::string& json);
std::string optional<std(const std::string& json);
std::string string> session;          // UIA(const std::string& json);
std::string MatrixError parseMatrixErrorJson(const std::string& json);
std::string getErrorDescription(const std(const std::string& json);
std::string string& errorCode);(const std::string& json);
std::string bool isPasswordError(const std(const std::string& json);
std::string string& errorCode);(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> getAllErrorCodes();(const std::string& json);
std::string matrixErrorToJson(const MatrixError& error);(const std::string& json);
std::string errorCode;(const std::string& json);
std::string errorMessage;(const std::string& json);
