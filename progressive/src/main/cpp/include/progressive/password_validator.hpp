#pragma once
#include <string>
#include <cstdint>

std::string strengthLabel;  // "Weak", "Fair", "Good", "Strong"(const std::string& json);
std::string feedback;       // human-readable suggestions(const std::string& json);
std::string PasswordResult validatePassword(const std(const std::string& json);
std::string string& password);(const std::string& json);
std::string bool meetsMinimumRequirements(const std(const std::string& json);
std::string string& password);(const std::string& json);
std::string int computePasswordStrength(const std(const std::string& json);
std::string string& password);(const std::string& json);
std::string getStrengthLabel(int strength);(const std::string& json);
std::string bool isCommonPassword(const std(const std::string& json);
std::string string& password);(const std::string& json);
std::string generatePasswordFeedback(const std(const std::string& json);
std::string string& password);(const std::string& json);
std::string int countCharClasses(const std(const std::string& json);
std::string string& password);(const std::string& json);
std::string double estimateCrackTimeSeconds(const std(const std::string& json);
std::string string& password);(const std::string& json);
std::string formatCrackTime(double seconds);(const std::string& json);
