#include "progressive/ignore_utils.hpp"
#include <chrono>
namespace progressive {
std::string buildIgnoreRequest(const std::string& uid) { return R"({"ignored_users":{"@me":{")"+uid+R"(":{}}}})"; }
std::vector<IgnoredUser> parseIgnoredUsers(const std::string& json) { std::vector<IgnoredUser> u; size_t p=0; while((p=json.find("\"@",p))!=std::string::npos){auto c=json.find(':',p);if(c!=std::string::npos&&c-p<50)u.push_back({json.substr(p+1,c-p-1)});p=c+1;} return u; }
bool isUserIgnored(const std::string& json, const std::string& uid) { return json.find(uid)!=std::string::npos; }
std::string buildUnignoreRequest(const std::string& uid) { return R"({"ignored_users":{"@me":{}})"; }
}
