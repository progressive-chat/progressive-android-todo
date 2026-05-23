#pragma once
#include <string>
#include <cstdint>

std::string id;              // e.g. "google", "github", "apple"(const std::string& json);
std::string name;            // e.g. "Google", "GitHub", "Apple"(const std::string& json);
std::string brand;           // brand identifier for icons(const std::string& json);
std::string iconUrl;         // optional icon URL(const std::string& json);
std::string rawType;         // original string from JSON(const std::string& json);
std::string requiredParameter;         // parameter name if required(const std::string& json);
std::string error;           // parse error message(const std::string& json);
std::string LoginAuthFlowsResult parseLoginFlows(const std::string& json);
std::string std(const std::string& json);
std::string vector<SsoProvider> parseSsoProviders(const std(const std::string& json);
std::string string& flowJson);(const std::string& json);
std::string loginFlowTypeToName(LoginFlowType type);(const std::string& json);
std::string loginFlowTypeDescription(LoginFlowType type);(const std::string& json);
std::string getSsoProviderIcon(const std(const std::string& json);
std::string string& providerId);(const std::string& json);
std::string loginFlowsToJson(const LoginAuthFlowsResult& result);(const std::string& json);
std::string std(const std::string& json);
std::string vector<std(const std::string& json);
std::string string> getSupportedLoginTypes();(const std::string& json);
