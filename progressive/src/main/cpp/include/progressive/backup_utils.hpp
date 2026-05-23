#pragma once
#include <string>
#include <cstdint>

std::string parseBackupInfo(const std::string& json);
std::string buildBackupKey(const std::string& json);
std::string encryptSessionData(const std::string& json);
std::string decryptSessionData(const std::string& json);
std::string verifyBackupIntegrity(const std::string& json);
