#pragma once
#include <string>
namespace progressive {
std::string formatMatrixError(const std::string& errcode, const std::string& error);
bool isRetryableError(const std::string& errcode);
bool isAuthError(const std::string& errcode);
bool isRateLimitError(const std::string& errcode);
std::string getFriendlyErrorMessage(const std::string& errcode);
}
