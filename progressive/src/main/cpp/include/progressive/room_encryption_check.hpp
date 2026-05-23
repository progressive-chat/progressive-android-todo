#pragma once
#include <string>
namespace progressive {
bool isRoomEncrypted(const std::string& stateJson);
std::string getEncryptionAlgorithm(const std::string& stateJson);
bool requiresEncryptionForFile(const std::string& roomState, const std::string& mimeType);
}
