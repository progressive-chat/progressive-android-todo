#include "progressive/matrix_id_utils.hpp"
namespace progressive {
std::string extractLocalpart(const std::string& mxid) { auto c=mxid.find(':'); return c!=std::string::npos?mxid.substr(1,c-1):mxid; }
std::string extractServerpart(const std::string& mxid) { auto c=mxid.find(':'); return c!=std::string::npos?mxid.substr(c+1):""; }
bool isValidMxid(const std::string& m) { return m.size()>3&&m.find(':')!=std::string::npos&&(m[0]=='@'||m[0]=='!'||m[0]=='#'||m[0]=='$'); }
bool isUserId(const std::string& m) { return !m.empty()&&m[0]=='@'; }
bool isRoomId(const std::string& m) { return !m.empty()&&m[0]=='!'; }
bool isEventId(const std::string& m) { return !m.empty()&&m[0]=='$'; }
}
