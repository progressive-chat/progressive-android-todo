#include "progressive/sync_filter_utils.hpp"
#include <sstream>

namespace progressive {
std::string buildRoomEventFilter(const std::vector<std::string>& types, bool inc) {
    std::ostringstream os; os << R"({"types":[)";
    for (size_t i = 0; i < types.size(); i++) { if (i > 0) os << ","; os << R"(")" << types[i] << R"(")"; }
    os << R"(],"not_types":[)";
    if (inc) { os << R"("m.room.member")"; } os << "]}"; return os.str();
}
std::string buildSyncFilter(int limit, bool lazy) {
    std::ostringstream os; os << R"({"room":{"timeline":{"limit":)" << limit << "}";
    if (lazy) os << R"(,"state":{"lazy_load_members":true})";
    os << R"(,"ephemeral":{"lazy_load_members":true}})";
    os << "}"; return os.str();
}
std::string buildRoomFilter(const std::vector<std::string>& ids, bool inc) {
    std::ostringstream os; os << R"({"rooms":[)";
    for (size_t i = 0; i < ids.size(); i++) { if (i > 0) os << ","; os << R"(")" << ids[i] << R"(")"; }
    os << "]}"; return os.str();
}
} // namespace progressive
