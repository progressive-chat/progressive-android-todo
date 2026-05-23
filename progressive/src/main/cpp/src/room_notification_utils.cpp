#include "progressive/room_notification_utils.hpp"
#include <sstream>
namespace progressive {
std::string buildRoomNotifOverride(const std::string& rid, const std::string& lvl) {
    std::ostringstream os; os << R"({"room_id":")" << rid << R"(","notification_level":")" << lvl << R"("})";
    return os.str();
}
std::string buildRoomNotifRemove(const std::string& rid) {
    return R"({"room_id":")" + rid + R"("})";
}
std::string formatNotifLevel(const std::string& lvl) {
    if (lvl == "all_messages") return "All messages";
    if (lvl == "mentions_only") return "Mentions only";
    if (lvl == "mute") return "Muted";
    return lvl;
}
}
