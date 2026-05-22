#include "progressive/room_permission_utils.hpp"

namespace progressive {

static std::string extractStr(const std::string& json, const std::string& key) {
    auto p = json.find("\"" + key + "\":\"");
    if (p == std::string::npos) return "";
    p += key.size() + 4;
    auto e = json.find('"', p);
    if (e == std::string::npos) return "";
    return json.substr(p, e - p);
}

RoomPermissions parseRoomPermissions(const std::string& joinRuleJson,
                                       const std::string& historyVisibilityJson,
                                       const std::string& guestAccessJson) {
    RoomPermissions p;
    p.joinRule = extractStr(joinRuleJson, "join_rule");
    if (p.joinRule.empty()) p.joinRule = "invite";
    p.historyVisibility = extractStr(historyVisibilityJson, "history_visibility");
    if (p.historyVisibility.empty()) p.historyVisibility = "shared";
    p.guestAccess = extractStr(guestAccessJson, "guest_access");
    if (p.guestAccess.empty()) p.guestAccess = "forbidden";
    return p;
}

bool canUserJoin(const RoomPermissions& perm, bool isInvited, bool isMember) {
    if (isMember) return false; // Already a member
    if (perm.joinRule == "public") return true;
    if (perm.joinRule == "knock") return true;
    if (perm.joinRule == "invite") return isInvited;
    if (perm.joinRule == "restricted") return isInvited;
    return false;
}

bool canUserReadHistory(const RoomPermissions& perm, const std::string& membership,
                          bool wasInvitedAtEventTime) {
    if (membership == "join") return true;
    if (perm.historyVisibility == "world_readable") return true;
    if (perm.historyVisibility == "shared" && (membership == "join" || wasInvitedAtEventTime)) return true;
    if (perm.historyVisibility == "invited" && (membership == "join" || membership == "invite")) return true;
    if (perm.historyVisibility == "joined" && membership == "join") return true;
    return false;
}

bool canGuestAccess(const RoomPermissions& perm) {
    return perm.guestAccess == "can_join";
}

bool isPublicRoom(const RoomPermissions& perm) {
    return perm.joinRule == "public";
}

bool isWorldReadable(const RoomPermissions& perm) {
    return perm.historyVisibility == "world_readable";
}

std::string formatJoinRule(const std::string& rule) {
    if (rule == "public") return "Anyone can join";
    if (rule == "invite") return "Invite only";
    if (rule == "knock") return "Knock to join";
    if (rule == "private") return "Private (invite only)";
    if (rule == "restricted") return "Restricted (invite or member of allowed space/room)";
    return rule;
}

std::string formatHistoryVisibility(const std::string& vis) {
    if (vis == "world_readable") return "Anyone can read history";
    if (vis == "shared") return "Members and previously invited";
    if (vis == "invited") return "Members and invited users";
    if (vis == "joined") return "Members only";
    return vis;
}

} // namespace progressive
