#pragma once
#include <string>
#include <cstdint>

std::string parseSsoConfig(const std::string& json);
std::string buildSsoLoginUrl(const std::string& json);
std::string parseTokenFromRedirect(const std::string& json);
std::string getIdentityProviderIcon(const std::string& json);
std::string formatSsoHtml(const std::string& json);
