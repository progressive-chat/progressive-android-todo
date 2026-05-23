#pragma once
#include <string>
namespace progressive {
std::string extractLocalpart(const std::string& mxid);
std::string extractServerpart(const std::string& mxid);
bool isValidMxid(const std::string& mxid);
bool isUserId(const std::string& mxid);
bool isRoomId(const std::string& mxid);
bool isEventId(const std::string& mxid);
}
