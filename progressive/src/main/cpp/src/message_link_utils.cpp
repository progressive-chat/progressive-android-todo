#include "progressive/message_link_utils.hpp"
#include <sstream>
namespace progressive {
std::string buildMessageLink(const std::string& rid, const std::string& eid) {
    return "https://matrix.to/#/" + rid + "/" + eid;
}
std::string buildUserLink(const std::string& uid) { return "https://matrix.to/#/" + uid; }
std::string buildRoomLink(const std::string& rid, const std::string& via) {
    std::string l = "https://matrix.to/#/" + rid; if (!via.empty()) l += "?via=" + via; return l;
}
}
