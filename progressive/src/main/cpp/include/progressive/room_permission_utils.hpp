#pragma once
#include <string>
#include <cstdint>

namespace progressive {

struct RoomPermissions {
    std::string roomId;
    std::string joinRule;           // "public", "invite", "knock", "private", "restricted"
    std::string historyVisibility;  // "world_readable", "shared", "invited", "joined"
    std::string guestAccess;        // "can_join", "forbidden"
    bool isEncrypted = false;
    bool isSpace = false;
};

// Parse room permissions from state events
RoomPermissions parseRoomPermissions(const std::string& joinRuleJson,
                                      const std::string& historyVisibilityJson,
                                      const std::string& guestAccessJson);

// Check various access conditions
bool canUserJoin(const RoomPermissions& perm, bool isInvited, bool isMember);
bool canUserReadHistory(const RoomPermissions& perm, const std::string& membership,
                         bool wasInvitedAtEventTime = false);
bool canGuestAccess(const RoomPermissions& perm);
bool isPublicRoom(const RoomPermissions& perm);
bool isWorldReadable(const RoomPermissions& perm);

// Format permissions for display
std::string formatJoinRule(const std::string& rule);
std::string formatHistoryVisibility(const std::string& visibility);

} // namespace progressive
